#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/SliderAnimatedLPI.h"

#include "../../Helpers/LPI_UnitTestHelper.h"
#include "../../../Light Server/src/LPE.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"03010000020FF000000FF00"
#define INVALID_LPI_INS		""

namespace LS
{
	namespace LPIS {
		namespace Slider {
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
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000020FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(7, steps);
				}

				TEST_METHOD(Is5WhenWidthIs4)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000040FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(5, steps);
				}

				TEST_METHOD(Is6WhenWidthIs3)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000030FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(6, steps);
				}

				TEST_METHOD(Is0WhenWidthIsInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000080FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

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
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, VALID_LPI_INS);
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint8_t opcode = lpi->GetOpCode();

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
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, VALID_LPI_INS);
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, INVALID_LPI_INS);
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIIsNull)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, nullptr);
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_DurationIsInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, INVALID_LPI_INS, 0);
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_WidthGreaterThanHalfLEDs)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000050FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsTrue_WidthLessThanHalfLEDs)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000040FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_WidthIs0)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000000FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_StartIs2)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000022FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsTrue_StartIs0_Near)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03100000020FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsTrue_StartIs1_Far)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000021FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_BackgroundColourMissing)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "0301000002100FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LEDAndBackgroundColoursMissing)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000021");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}
			};

			TEST_CLASS(SliderAnimatedLPI_GetNextRI)
			{
			public:
				TEST_METHOD(NextRIReturnsTrue_InsIsValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, VALID_LPI_INS);
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsFalse_LPIInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, INVALID_LPI_INS);
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_Step1In8LEDs2LEDWidthSlider_Near)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000020FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FF00000200FF0006", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_Step4In8LEDs2LEDWidthSlider_Near)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000020FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 3; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("00FF0003FF00000200FF0003", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_Step7In8LEDs2LEDWidthSlider_Near)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000020FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 6; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("00FF0006FF000002", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsFalseNoMoreRIs_Step8In8LEDs2LEDWidthSlider_Near)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000020FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 7; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					bool hasNextRi = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(false, hasNextRi);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_Step1In8LEDs2LEDWidthSlider_Far)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000021FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("00FF0006FF000002", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_Step4In8LEDs2LEDWidthSlider_Far)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000021FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 3; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					bool hasNextRi = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("00FF0003FF00000200FF0003", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_Step7In8LEDs2LEDWidthSlider_Far)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000021FF000000FF00");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 6; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					bool hasNextRi = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FF00000200FF0006", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsFalseNoMoreRIs_Step8In8LEDs2LEDWidthSlider_Far)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Slider, "03010000021FF000000FF00c");
					SliderAnimatedLPI* lpi = (SliderAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 7; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					bool hasNextRi = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(false, hasNextRi);
					lpiInstantiator.CleanUp(lpi);
				}
			};
		}
	}
}