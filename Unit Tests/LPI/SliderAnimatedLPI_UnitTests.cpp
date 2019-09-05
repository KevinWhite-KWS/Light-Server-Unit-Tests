#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/SliderAnimatedLPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"03010000020FF000000FF00"
#define INVALID_LPI_INS		""

namespace LS
{
	// Effect LPI:
	// 03010000 = 03 (op-code), 01 (duration), 00 (reserved), 00 (reserved)
	// 020 = 02 (slider width in pixels), 0 (0 = start near, 1 = start far)
	// FF0000 = slider colour (red)
	// 00FF00 = back ground colour (green)
	// e.g. 03010000020FF000000FF00

	// Validation:
	// width is < half available pixels (rounded down)
	// 0 or 1 for starting
	// valid slider colour
	// valid background colour

	// Tests ensure that the correct total number of steps
	// are reported by the effect.
	// The total steps calculated as: steps = numLEDS - slider width + 1
	TEST_CLASS(SliderAnimatedLPI_GetTotalNumberOfSteps)
	{
	public:
		TEST_METHOD(Is7WhenWidthIs2)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000020FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(7, steps);
		}

		TEST_METHOD(Is5WhenWidthIs4)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000040FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(5, steps);
		}

		TEST_METHOD(Is6WhenWidthIs3)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000030FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(6, steps);
		}

		TEST_METHOD(Is0WhenWidthIsInvalid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000080FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(0, steps);
		}
	};

	TEST_CLASS(SliderAnimatedLPI_GetOpCode)
	{
	public:
		TEST_METHOD(Is3)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000080FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(0, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			uint8_t opcode = lpi.GetOpCode();

			// assert
			Assert::AreEqual<uint8_t>(3, opcode);
		}
	};

	TEST_CLASS(SliderAnimatedLPI_Validate)
	{
	public:
		TEST_METHOD(ValiateReturnsTrue_LPIValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000020FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_OpCodeIsNot03)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("01010000020FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(0, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			lpiBuffer.LoadFromBuffer("03000000020FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 0, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_WidthGreaterThanHalfLEDs)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000050FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsTrue_WidthLessThanHalfLEDs)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000040FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_WidthIs0)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000000FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_StartIs2)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000022FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsTrue_StartIs0_Near)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03100000020FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsTrue_StartIs1_Far)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000021FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_BackgroundColourMissing)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0301000002100FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_LEDAndBackgroundColoursMissing)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000021");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}
	};

	TEST_CLASS(SliderAnimatedLPI_GetNextRI)
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
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

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
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(false, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_Step1In8LEDs2LEDWidthSlider_Near)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000020FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FF00000200FF006", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_Step4In8LEDs2LEDWidthSlider_Near)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000020FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer); // step 1
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 2
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 3
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 4

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("00FF0003FF00000200FF003", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_Step7In8LEDs2LEDWidthSlider_Near)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000020FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer); // step 1
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 2
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 3
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 4
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 5
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 6
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 7

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("00FF0007FF000001", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsFalseNoMoreRIs_Step8In8LEDs2LEDWidthSlider_Near)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000020FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer); // step 1
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 2
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 3
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 4
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 5
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 6
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 7
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 8

			// assert
			Assert::AreEqual<bool>(false, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_Step1In8LEDs2LEDWidthSlider_Far)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000021FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("00FF0007FF000001", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_Step4In8LEDs2LEDWidthSlider_Far)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000021FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer); // step 1
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 2
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 3
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 4

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("00FF0003FF00000200FF003", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsExpectedRI_Step7In8LEDs2LEDWidthSlider_Far)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000021FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer); // step 1
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 2
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 3
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 4
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 5
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 6
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 7

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FF00000100FF0007", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsFalseNoMoreRIs_Step8In8LEDs2LEDWidthSlider_Far)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("03010000021FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(3, 1, &lpiBuffer);
			SliderAnimatedLPI lpi = SliderAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer); // step 1
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 2
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 3
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 4
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 5
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 6
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 7
			nextRiRet = lpi.GetNextRI(&riBuffer); // step 8

			// assert
			Assert::AreEqual<bool>(false, nextRiRet);
		}
	};
}