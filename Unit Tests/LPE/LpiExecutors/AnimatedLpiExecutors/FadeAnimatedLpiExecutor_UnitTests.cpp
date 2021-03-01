#include "CppUnitTest.h"

#include "..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\AnimatedLpiExecutors\FadeAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Fade {
				TEST_CLASS(ValidateLpi)
				{
				public:
					TEST_METHOD(WhenValidFadeLpi_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("04010000020FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenStepValueIs0_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("04010000000FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenStepValueIs51_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("04010000330FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenStepValueIs1_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("04010000010FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenStepValueIs50_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("04010000320FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenStepValueIs25_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("04010000190FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenFadeInIs1_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("04010000021FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenFadeInIs2_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("04010000022FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenMissingEndColourFalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("04010000020FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenMissingStartColourFalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("04010000020");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}
				};

				TEST_CLASS(GetNumberOfSteps)
				{
				public:
					TEST_METHOD(WhenStepValue5Start000000EndFFFFFF_StepsAre52)
					{
						// arrange
						LpiExecutor_Tester tester("04010000050000000FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(52, steps);
					}

					TEST_METHOD(WhenStepValue10Start000000EndFFFFFF_StepsAre27)
					{
						// arrange
						LpiExecutor_Tester tester("040100000A0000000FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(27, steps);
					}

					TEST_METHOD(WhenStepValue20Start000000EndFFFFFF_StepsAre14)
					{
						// arrange
						LpiExecutor_Tester tester("04010000140000000FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(14, steps);
					}

					TEST_METHOD(WhenStepValue1Start000000EndFFFFFF_StepsAre256)
					{
						// arrange
						LpiExecutor_Tester tester("04010000010000000FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(256, steps);
					}

					TEST_METHOD(WhenFadeInStep50_StepsAre7)
					{
						// arrange
						LpiExecutor_Tester tester("04010000320000000FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(7, steps);
					}

					TEST_METHOD(WhenFadeOutStep50_StepsAre7)
					{
						// arrange
						LpiExecutor_Tester tester("04010000321FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(7, steps);
					}

					TEST_METHOD(WhenFadeInStep27_StepsAre6)
					{
						// arrange
						LpiExecutor_Tester tester("040100001B0575B5FC9CBCD");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(6, steps);
					}

					TEST_METHOD(WhenFadeOutStep33_StepsAre5)
					{
						// arrange
						LpiExecutor_Tester tester("04010000211979182231B1F");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(5, steps);
					}

					TEST_METHOD(WhenFadeInStep10_StepsAre1)
					{
						// arrange
						LpiExecutor_Tester tester("040100000A0FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(1, steps);
					}
				};

				TEST_CLASS(Execute)
				{
				public:
					TEST_METHOD(WhenNullOutput_Return)
					{
						// arrange
						FadeAnimatedLpiExecutor lpiExecutor;

						// act
						lpiExecutor.Execute(nullptr, 0, nullptr);

						// assert
					}

					TEST_METHOD(WhenFadeInStep1_000000ToFFFFFF_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000010000000FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsTrue(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenFadeInStep4_000000ToFFFFFF_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000320000000FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 3, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(150,150,150), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsTrue(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenFadeInStep6_000000ToFFFFFF_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000320000000FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 5, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(250,250,250), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsTrue(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenFadeInStep7_000000ToFFFFFF_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000320000000FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 6, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,255,255), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsTrue(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenFadeInStep8_000000ToFFFFFF_RIsNotSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000320000000FFFFFF");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 7, &output);

						// assert
						Assert::IsFalse(output.RenderingInstructionsSet());
					}

					TEST_METHOD(WhenFadeOutStep1_FFFFFFTo000000_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000321FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,255,255), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeOutStep2_FFFFFFTo000000_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000321FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 1, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(205,205,205), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeOutStep4_FFFFFFTo000000_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000321FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 3, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(105,105,105), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeOutStep7_FFFFFFTo000000_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000321FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 6, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeOutStep8_FFFFFFTo000000_RIsNotSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000321FFFFFF000000");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 7, &output);

						// assert
						Assert::IsFalse(output.RenderingInstructionsSet());
					}

					TEST_METHOD(WhenFadeInStep1_575B5FToC9CBCD_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("040100001B0575B5FC9CBCD");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(87,91,95), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeIntStep4_575B5FToC9CBCD_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("040100001B0575B5FC9CBCD");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 3, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(168,172,176), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeIntStep6_575B5FToC9CBCD_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("040100001B0575B5FC9CBCD");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 5, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(201,203,205), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeOuttStep1_97918ETo231200__RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0401000021197918E231200");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(151,145,142), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeOuttStep3_97918ETo231200__RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0401000021197918E231200");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 2, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(85,79,76), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeOuttStep6_97918ETo231200__RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0401000021197918E231200");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 5, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(35,18,00), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeOutStep1_FF0000To000000__RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000321FF0000000000");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeOutStep2_FF0000To000000__RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000321FF0000000000");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 1, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(205,0,0), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenFadeOutStep3_FF0000To000000__RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("04010000321FF0000000000");
						FadeAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 2, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(155,0,0), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}
				};
			}
		}
	}
}