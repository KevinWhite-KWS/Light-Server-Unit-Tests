#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/StochasticNonAnimatedLPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"0501000002FF000000FF00"
#define INVALID_LPI_INS		""

namespace LS
{
	TEST_CLASS(StochasticNonAnimatedLPI_GetTotalNumberOfSteps)
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
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(1, steps);
		}
	};

	TEST_CLASS(StochasticNonAnimatedLPI_GetOpCode)
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
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			uint8_t opcode = lpi.GetOpCode();

			// assert
			Assert::AreEqual<uint8_t>(5, opcode);
		}
	};

	TEST_CLASS(StochasticNonAnimatedLPI_Validate)
	{
	public:
		TEST_METHOD(ValiateReturnsTrue_LPIValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_OpCodeIsNot05)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("00010000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(0, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			lpiBuffer.LoadFromBuffer("05000000FFFFFF");
			LPIInstruction lpiIns = LPIInstruction(5, 0, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_00Elements)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000000");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_01Elements)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000001FF0000");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_33Elements)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000033FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsTrue_32Elements)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000032FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_TwoElementsMissingColour)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000002FF0000");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_ThreeElementsMissingColour)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000003FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_ThreeElementsMissingTwoColours)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000003FF0000");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_ThreeElementsMissingThreeColours)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000003");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}
	};

	TEST_CLASS(StochasticNonAnimatedLPI_GetNextRI)
	{
	public:
		TEST_METHOD(NextRIReturnsTrue_InsIsValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(INVALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(1, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(false, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsTrue_LEDsAreRedAndGreen)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000002FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int countValidLEDs = 0;
			bool isValid = false;
			while (*pRiBuffer && countValidLEDs <= 8) {
				Colour colour = stringProcessor.ExtractColourFromHexEncoded(pRiBuffer, isValid);
				pRiBuffer += 6;
				int leds = stringProcessor.ExtractNumberFromHexEncoded(pRiBuffer, 1, 255, isValid);
				pRiBuffer += 2;
				if ((colour.red == 255 && colour.green == 0 && colour.blue == 0) ||
					(colour.red == 0 && colour.green == 255 && colour.blue == 0)) {
					countValidLEDs += leds;
				}
			}
			
			Assert::AreEqual<int>(8, countValidLEDs);
		}

		TEST_METHOD(NextRIReturnsTrue_LEDsAreRedAndGreenAndBlue)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000003FF000000FF000000FF");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int countValidLEDs = 0;
			bool isValid = false;
			while (*pRiBuffer && countValidLEDs <= 8) {
				Colour colour = stringProcessor.ExtractColourFromHexEncoded(pRiBuffer, isValid);
				pRiBuffer += 6;
				int leds = stringProcessor.ExtractNumberFromHexEncoded(pRiBuffer, 1, 255, isValid);
				pRiBuffer += 2;
				if ((colour.red == 255 && colour.green == 0 && colour.blue == 0) ||
					(colour.red == 0 && colour.green == 255 && colour.blue == 0) ||
					(colour.red == 0 && colour.green == 0 && colour.blue == 255)) {
					countValidLEDs += leds;
				}
			}

			Assert::AreEqual<int>(8, countValidLEDs);
		}

		TEST_METHOD(NextRIReturnsTrue_LEDsAreAABBCCAnd010203)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0501000002AABBCC010203");
			LPIInstruction lpiIns = LPIInstruction(5, 1, &lpiBuffer);
			StochasticNonAnimatedLPI lpi = StochasticNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int countValidLEDs = 0;
			bool isValid = false;
			while (*pRiBuffer && countValidLEDs <= 8) {
				Colour colour = stringProcessor.ExtractColourFromHexEncoded(pRiBuffer, isValid);
				pRiBuffer += 6;
				int leds = stringProcessor.ExtractNumberFromHexEncoded(pRiBuffer, 1, 255, isValid);
				pRiBuffer += 2;
				if ((colour.red == 170 && colour.green == 187 && colour.blue == 204) ||
					(colour.red == 1 && colour.green == 2 && colour.blue == 3)) {
					countValidLEDs += leds;
				}
			}

			Assert::AreEqual<int>(8, countValidLEDs);
		}

	};
}