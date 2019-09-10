#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/PatternNonAnimatedLPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"0201000002010200FF00FF0000"
#define INVALID_LPI_INS		""
#define VALID_NEXT_RI		"00000001R"

namespace LS
{
	TEST_CLASS(PatternNonAnimatedLPI_GetTotalNumberOfSteps)
	{
	public:
		TEST_METHOD(IsOne)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(0, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(1, steps);
		}
	};

	TEST_CLASS(PatternNonAnimatedLPI_GetOpCode)
	{
	public:
		TEST_METHOD(Is2)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			uint8_t opcode = lpi.GetOpCode();

			// assert
			Assert::AreEqual<uint8_t>(2, opcode);
		}
	};

	TEST_CLASS(PatternNonAnimatedLPI_Validate)
	{
	public:
		TEST_METHOD(ValiateReturnsTrue_LPIValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_LPIInvalid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(INVALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_OpCodeIsNot02)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0301000002010200FF00FF0000");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_LPIIsNull)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(nullptr);
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_DurationIsInvalid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0200000002010200FF00FF0000");
			LPIInstruction lpiIns = LPIInstruction(2, 0, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_0Blocks)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0201000000010200FF00FF0000");
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_2BlocksMissing1)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("02010000020200FF00FF0000");
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_2BlocksMissing1Colour)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0201000002010200FF00");
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_BlocksExceedsLEDS)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0201000002040500FF00FF0000");
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

	};

	TEST_CLASS(PatternNonAnimatedLPI_GetNextRI)
	{
	public:
		TEST_METHOD(NextRIReturnsTrue_InsIsValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(true, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsFalse_LPIInvalid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(INVALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(false, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsTrue_ColourIsHalfGreenAndHalfRed)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0201000002040400FF00FF0000");
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("00FF0004FF000004R", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsTrue_AlternateRedGreen)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("02010000020101FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FF00000100FF0001R", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsTrue_ThreeGroups)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0201000003030201FF000000FF000000FF");
			LPIInstruction lpiIns = LPIInstruction(2, 1, &lpiBuffer);
			PatternNonAnimatedLPI lpi = PatternNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FF00000300FF00020000FF01R", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}
	};
}