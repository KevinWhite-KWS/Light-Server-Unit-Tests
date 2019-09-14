#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/FadeAnimatedLPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"04010000320000000FFFFFF"
#define INVALID_LPI_INS		""

namespace LS
{
	// Effect LPI:
	// 04010000 = 04 (op-code), 01 (duration), 00 (reserved), 00 (reserved)
	// 0A0 = 0A (step size), 0 (0 = fade-in, 1 = fade-out)
	// 000000 = start colour
	// FFFFFF = end colour
	// e.g. 040100000A0000000FFFFFF

	// Validation:
	// step is between 1 and 50
	// 0 or 1 for fade-in or fade-out
	// valid start colour
	// valid end colour

	// Tests ensure that the correct total number of steps
	// are reported by the effect.
	// The total steps calculated as: steps = ROUNDUP(MAX(EndR-StartR,EndG-StartG,EndB-StartB) / Step + 1)
	TEST_CLASS(FadeAnimatedLPI_GetTotalNumberOfSteps)
	{
	public:
		TEST_METHOD(Is7WhenFadeInStep50)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000320000000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(7, steps);
		}

		TEST_METHOD(Is7WhenFadeOutStep50)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000321FFFFFF000000");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(7, steps);
		}

		TEST_METHOD(Is6WhenFadeInStep27)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("040100001B0575B5FC9CBCD");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(6, steps);
		}

		TEST_METHOD(Is5WhenFadeOutStep33)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000211979182231B1F");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(5, steps);
		}

		TEST_METHOD(Is1WhenFadeInStep10_StartExceedsEnd)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("040100000A0FFFFFF000000");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(1, steps);
		}
	};

	TEST_CLASS(FadeAnimatedLPI_GetOpCode)
	{
	public:
		TEST_METHOD(Is4)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000211979182231B1F");
			LPIInstruction lpiIns = LPIInstruction(0, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			uint8_t opcode = lpi.GetOpCode();

			// assert
			Assert::AreEqual<uint8_t>(4, opcode);
		}
	};

	TEST_CLASS(FadeAnimatedLPI_Validate)
	{
	public:
		TEST_METHOD(ValiateReturnsTrue_LPIValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_LPIInvalid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(INVALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_OpCodeIsNot04)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("01010000211979182231B1F");
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_LPIIsNull)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(nullptr);
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_StepIs0)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000001979182231B1F");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_StepIs51)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000331979182231B1F");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsTrue_StepIs50)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000321979182231B1F");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsTrue_StepIs1)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000011979182231B1F");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsTrue_FadeIs0)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000010979182231B1F");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsTrue_FadeIs1)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000011979182231B1F");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_FadeIs2)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000012979182231B1F");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_StartColourMissing)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000010231B1F");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_ColoursMissing)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000010");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}
	};

	TEST_CLASS(FadeAnimatedLPI_GetNextRI)
	{
	public:
		TEST_METHOD(NextRIReturnsTrue_InsIsValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(true, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsFalse_LPIInvalid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(INVALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(false, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_BlackToWhite_Step1_Black)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000320000000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("00000008", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_BlackToWhite_Step4_969696)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000320000000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("96969608", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_BlackToWhite_Step6_FAFAFA)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000320000000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FAFAFA08", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_BlackToWhite_Step7_FFFFFF)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000320000000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FFFFFF08", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_BlackToWhite_Step8_FalseReturned)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000320000000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			nextRiRet = lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(false, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_WhiteToBlack_Step1_White)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000321FFFFFF000000");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FFFFFF08", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_WhiteToBlack_Step2_CDCDCD)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000321FFFFFF000000");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("CDCDCD08", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_WhiteToBlack_Step4_696969)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000321FFFFFF000000");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("69696908", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_WhiteToBlack_Step7_Black)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000321FFFFFF000000");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("00000008", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_WhiteToBlack_Step8_FalseReturned)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000321FFFFFF000000");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(false, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_575B5FToC9CBCD_Step1_575B5F)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("040100001B0575B5FC9CBCD");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("575B5F08", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_575B5FToC9CBCD_Step4_A8ACB0)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("040100001B0575B5FC9CBCD");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("A8ACB008", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_575B5FToC9CBCD_Step6_C9CBCD)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("040100001B0575B5FC9CBCD");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("C9CBCD08", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_97918ETo231200_Step1_97918E)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0401000021197918E231200");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("97918E08", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_97918ETo231200_Step3_554F4C)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0401000021197918E231200");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("554F4C08", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_97918ETo231200_Step6_554F4C)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0401000021197918E231200");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			lpi.GetNextRI(&riBuffer);
			riBuffer.ClearBuffer();
			nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("23120008", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_WhiteToBlack_Step1_Black)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("04010000210FFFFFF000000");
			LPIInstruction lpiIns = LPIInstruction(4, 1, &lpiBuffer);
			FadeAnimatedLPI lpi = FadeAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("00000008", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}
	};
}