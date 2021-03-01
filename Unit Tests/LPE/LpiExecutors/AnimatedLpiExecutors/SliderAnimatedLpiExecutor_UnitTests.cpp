#include "CppUnitTest.h"

#include "..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\AnimatedLpiExecutors\SliderAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Slider {
				TEST_CLASS(ValidateLpi)
				{
				public:
					TEST_METHOD(WhenValidSliderLpi_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("03010000020FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenSliderWidth0_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("03010000000FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenSliderWidth51_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("03010000330FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenSliderWidth1_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("03010000010FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenSliderWidth50_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("03010000320FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenSliderWidth25_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("03010000190FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenStartNearIs1_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("03010000021FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenStartNearIs2_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("03010000022FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenNoBackgroundColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("03010000020FFFFFF");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenNoSliderColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("03010000020");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}
				};

				TEST_CLASS(GetNumberOfSteps)
				{
				public:
					TEST_METHOD(When8LedsSlider2Wide_NumberOfStepsIs7)
					{
						// arrange
						LpiExecutor_Tester tester("03010000020FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(7, steps);
					}

					TEST_METHOD(When8LedsSlider4Wide_NumberOfStepsIs5)
					{
						// arrange
						LpiExecutor_Tester tester("03010000040FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(5, steps);
					}

					TEST_METHOD(When8LedsSlider6Wide_NumberOfStepsIs6)
					{
						// arrange
						LpiExecutor_Tester tester("03010000060FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(3, steps);
					}

					TEST_METHOD(When8LedsSlider8Wide_NumberOfStepsIs1)
					{
						// arrange
						LpiExecutor_Tester tester("03010000080FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(1, steps);
					}

					TEST_METHOD(When100LedsSlider50Wide_NumberOfStepsIs51)
					{
						// arrange
						LpiExecutor_Tester tester("03010000321FFFFFF000000", 100);
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(51, steps);
					}
				};

				TEST_CLASS(Execute)
				{
				public:
					TEST_METHOD(WhenNullOutput_Return)
					{
						// arrange
						SliderAnimatedLpiExecutor lpiExecutor;

						// act
						lpiExecutor.Execute(nullptr, 0, nullptr);

						// assert
					}

					TEST_METHOD(WhenStartNear8LedsStep1_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000020FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 2;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,255,255), 2),
							RI(Colour(0,0,0), 6)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStartNear8LedsStep2_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000020FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 1, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 1),
							RI(Colour(255,255,255), 2),
							RI(Colour(0,0,0), 5)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStartNear8LedsStep5_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000020FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 5, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 5),
							RI(Colour(255,255,255), 2),
							RI(Colour(0,0,0), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStartNear8LedsStep7_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000020FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 6, &output);

						// assert
						const int numRisExpected = 2;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 6),
							RI(Colour(255,255,255), 2)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStartNear8LedsStep8_RIsNotSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000020FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 7, &output);

						// assert
						Assert::IsFalse(output.RenderingInstructionsSet());
					}

					TEST_METHOD(WhenStartFar8LedsStep1_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000021FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 2;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 6),
							RI(Colour(255,255,255), 2)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStartFar8LedsStep2_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000021FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 1, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 5),
							RI(Colour(255,255,255), 2),
							RI(Colour(0,0,0), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStartFar8LedsStep5_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000021FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 5, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 1),
							RI(Colour(255,255,255), 2),
							RI(Colour(0,0,0), 5)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStartFar8LedsStep7_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000021FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 6, &output);

						// assert
						const int numRisExpected = 2;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,255,255), 2),
							RI(Colour(0,0,0), 6)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStartFar8LedsStep8_RIsNotSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000021FFFFFF000000");
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 7, &output);

						// assert
						Assert::IsFalse(output.RenderingInstructionsSet());
					}

					TEST_METHOD(WhenStartNear100LedsSliderWidth50Step25_RIsNotSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000320FFFFFF000000", 100);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 24, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 24),
							RI(Colour(255,255,255), 50),
							RI(Colour(0,0,0), 26)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStartFar100LedsSliderWidth50Step25_RIsNotSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000321FFFFFF000000", 100);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 24, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 26),
							RI(Colour(255,255,255), 50),
							RI(Colour(0,0,0), 24)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}
				};
			}
		}
	}
}