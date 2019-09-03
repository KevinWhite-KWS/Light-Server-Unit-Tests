#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/SolidNonAnimatedLPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"01010000FFFFFF"
#define INVALID_LPI_INS		""
#define VALID_NEXT_RI		"00000001R"

namespace LS
{
	TEST_CLASS(SolidNonAnimatedLPI_GetTotalNumberOfSteps)
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
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(1, steps);
		}
	};

	TEST_CLASS(SolidNonAnimatedLPI_GetOpCode)
	{
	public:
		TEST_METHOD(Is1)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			uint8_t opcode = lpi.GetOpCode();

			// assert
			Assert::AreEqual<uint8_t>(1, opcode);
		}
	};

	TEST_CLASS(SolidNonAnimatedLPI_Validate)
	{
	public:
		TEST_METHOD(ValiateReturnsTrue_LPIValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_OpCodeIsNot01)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("00010000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(0, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			lpiBuffer.LoadFromBuffer("01000000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(1, 0, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_MissingColour)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("01010000");
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_InvalidColour)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("01010000FFFFFH");
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}
	};

	TEST_CLASS(SolidNonAnimatedLPI_GetNextRI)
	{
	public:
		TEST_METHOD(NextRIReturnsTrue_InsIsValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(INVALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(false, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsTrue_ColourIsWhite)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("01010000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FFFFFF01R", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsTrue_ColourIsBlack)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("01010000000000");
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("00000001R", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsTrue_ColourIsFixed)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("01010000FA052A");
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			SolidNonAnimatedLPI lpi = SolidNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FA052A01R", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}
	};
}