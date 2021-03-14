#include "CppUnitTest.h"

#include "..\..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\AnimatedLpiExecutors\SliderAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

#define LPI	"030100000200032FF00000000FF"

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Slider {
				

				TEST_CLASS(Execute)
				{
				public:
					TEST_METHOD(WhenTail50PercentRedBlueStep1_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 2;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0), 2),
							RI(Colour(0,0,255), 8)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenTail50PercentRedBlueStep2_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 1, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(204,0,51), 1),
							RI(Colour(255,0,0), 2),
							RI(Colour(0,0,255), 7)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenTail50PercentRedBlueStep5_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 4, &output);

						// assert
						const int numRisExpected = 6;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(51,0,204), 1),
							RI(Colour(102,0,153), 1),
							RI(Colour(153,0,102), 1),
							RI(Colour(204,0,51), 1),
							RI(Colour(255,0,0), 2),
							RI(Colour(0,0,255), 4)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenTail50PercentRedBlueStep8_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 7, &output);

						// assert
						const int numRisExpected = 7;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,255), 3),
							RI(Colour(51,0,204), 1),
							RI(Colour(102,0,153), 1),
							RI(Colour(153,0,102), 1),
							RI(Colour(204,0,51), 1),
							RI(Colour(255,0,0), 2),
							RI(Colour(0,0,255), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenTail50PercentRedBlueStep9_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 8, &output);

						// assert
						const int numRisExpected = 6;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,255), 4),
							RI(Colour(51,0,204), 1),
							RI(Colour(102,0,153), 1),
							RI(Colour(153,0,102), 1),
							RI(Colour(204,0,51), 1),
							RI(Colour(255,0,0), 2)
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