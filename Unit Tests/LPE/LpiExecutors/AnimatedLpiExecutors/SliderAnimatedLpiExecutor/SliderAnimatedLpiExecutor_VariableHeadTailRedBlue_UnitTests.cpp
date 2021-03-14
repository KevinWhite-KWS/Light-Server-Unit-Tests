#include "CppUnitTest.h"

#include "..\..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\AnimatedLpiExecutors\SliderAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

#define SLIDERCOLOUR Colour(255,0,0)
#define BACKGROUNDCOLOUR Colour(0,0,255)

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Slider {
				TEST_CLASS(Execute)
				{
				public:
					TEST_METHOD(WhenHead100PercentTail25PercentRedBlueStep4_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("030100000206419FF00000000FF", 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 3, &output);

						// assert
						const int numRisExpected = 9;
						RI expectedRIs[numRisExpected] = {
							RI(BACKGROUNDCOLOUR, 1),
							RI(Colour(85,0,170), 1),
							RI(Colour(170,0,85), 1),
							RI(SLIDERCOLOUR, 2),
							RI(Colour(227,0,28),1),
							RI(Colour(198,0,57),1),
							RI(Colour(170,0,85),1),
							RI(Colour(142,0,113),1),
							RI(Colour(113,0,142),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenHead25PercentTail100PercentRedBlueStep4_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("030100000201964FF00000000FF", 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 3, &output);

						// assert
						const int numRisExpected = 7;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(170,0,85),1),
							RI(Colour(198,0,57),1),
							RI(Colour(227,0,28),1),
							RI(SLIDERCOLOUR, 2),
							RI(Colour(170,0,85),1),
							RI(Colour(85,0,170),1),
							RI(BACKGROUNDCOLOUR,3)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenHead100PercentTail13PercentRedBlueStep2_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("03010000020640DFF00000000FF", 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 1, &output);

						// assert
						const int numRisExpected = 9;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(128,0,128),1),
							RI(SLIDERCOLOUR, 2),
							RI(Colour(227,0,28),1),
							RI(Colour(198,0,57),1),
							RI(Colour(170,0,85),1),
							RI(Colour(142,0,113),1),
							RI(Colour(113,0,142),1),
							RI(Colour(85,0,170),1),
							RI(Colour(57,0,198),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenHead13PercentTail100PercentRedBlueStep2_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("030100000200D64FF00000000FF", 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 1, &output);

						// assert
						const int numRisExpected = 4;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(227,0,28),1),
							RI(SLIDERCOLOUR, 2),
							RI(Colour(128,0,128),1),
							RI(BACKGROUNDCOLOUR,6)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenHead100PercentTail100PercentRedBlueStep6_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("030100000206464FF00000000FF", 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 5, &output);

						// assert
						const int numRisExpected = 9;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(113,0,142),1),
							RI(Colour(142,0,113),1),
							RI(Colour(170,0,85),1),
							RI(Colour(198,0,57),1),
							RI(Colour(227,0,28),1),
							RI(SLIDERCOLOUR, 2),
							RI(Colour(227,0,28),1),
							RI(Colour(198,0,57),1),
							RI(Colour(170,0,85),1)
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