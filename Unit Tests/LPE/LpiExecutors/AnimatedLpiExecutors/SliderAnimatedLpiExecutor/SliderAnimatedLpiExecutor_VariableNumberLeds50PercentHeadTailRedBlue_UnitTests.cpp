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
					TEST_METHOD(When20LedsStep10_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("030100000203232FF00000000FF", 20);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 9, &output);

						// assert
						const int numRisExpected = 19;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(26,0,230),1),
							RI(Colour(51,0,204),1),
							RI(Colour(77,0,179),1),
							RI(Colour(102,0,153),1),
							RI(Colour(128,0,128),1),
							RI(Colour(153,0,102),1),
							RI(Colour(179,0,77),1),
							RI(Colour(204,0,51),1),
							RI(Colour(230,0,26),1),
							RI(SLIDERCOLOUR, 2),
							RI(Colour(230,0,26),1),
							RI(Colour(204,0,51),1),
							RI(Colour(179,0,77),1),
							RI(Colour(153,0,102),1),
							RI(Colour(128,0,128),1),
							RI(Colour(102,0,153),1),
							RI(Colour(77,0,179),1),
							RI(Colour(51,0,204),1),
							RI(Colour(26,0,230),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(When18LedsStep9_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("030100000201919FF00000000FF", 18);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 8, &output);

						// assert
						const int numRisExpected = 11;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(BACKGROUNDCOLOUR),4),
							RI(Colour(51,0,204),1),
							RI(Colour(102,0,153),1),
							RI(Colour(153,0,102),1),
							RI(Colour(204,0,51),1),
							RI(SLIDERCOLOUR, 2),
							RI(Colour(204,0,51),1),
							RI(Colour(153,0,102),1),
							RI(Colour(102,0,153),1),
							RI(Colour(51,0,204),1),
							RI(Colour(BACKGROUNDCOLOUR),4)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(When14LedsStep7_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("030100000206464FF00000000FF", 14);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 6, &output);

						// assert
						const int numRisExpected = 13;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(137,0,118),1),
							RI(Colour(157,0,98),1),
							RI(Colour(177,0,78),1),
							RI(Colour(196,0,59),1),
							RI(Colour(216,0,39),1),
							RI(Colour(235,0,20),1),
							RI(SLIDERCOLOUR, 2),
							RI(Colour(235,0,20),1),
							RI(Colour(216,0,39),1),
							RI(Colour(196,0,59),1),
							RI(Colour(177,0,78),1),
							RI(Colour(157,0,98),1),
							RI(Colour(137,0,118),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(When18LedsStep1_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("030100000203232FF000000FF00", 18);
						// "030100000206464FF00000000FF"
						// "030100000203232FF000000FF00"
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 10;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(SLIDERCOLOUR), 2),
							RI(Colour(227,28,0),1),
							RI(Colour(198,57,0),1),
							RI(Colour(170,85,0),1),
							RI(Colour(142,113,0),1),
							RI(Colour(113,142,0),1),
							RI(Colour(85,170,0),1),
							RI(Colour(57,198,0),1),
							RI(Colour(28,227,0),1),
							RI(Colour(0,255,0), 8)
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