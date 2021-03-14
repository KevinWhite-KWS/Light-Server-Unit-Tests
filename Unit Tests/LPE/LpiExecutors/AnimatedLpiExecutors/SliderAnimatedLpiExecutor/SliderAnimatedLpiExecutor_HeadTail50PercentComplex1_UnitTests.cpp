#include "CppUnitTest.h"

#include "..\..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\AnimatedLpiExecutors\SliderAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

#define LPI	"030100000203232FF9900CCFF66"

#define SLIDERCOLOUR Colour(255,153,0)
#define STEP1COLOUR Colour(245,173,20)
#define STEP2COLOUR Colour(235,194,41)
#define STEP3COLOUR Colour(224,214,61)
#define STEP4COLOUR Colour(214,235,82)
#define BACKGROUNDCOLOUR Colour(204,255,102)

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Slider {
				TEST_CLASS(Execute)
				{
				public:
					TEST_METHOD(WhenHeadTail50PercentComplex1Step1_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 6;
						RI expectedRIs[numRisExpected] = {
							RI(SLIDERCOLOUR, 2),
							RI(STEP1COLOUR, 1),
							RI(STEP2COLOUR, 1),
							RI(STEP3COLOUR, 1),
							RI(STEP4COLOUR, 1),
							RI(BACKGROUNDCOLOUR, 4)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenHeadTail50PercentComplex1Step2_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 1, &output);

						// assert
						const int numRisExpected = 7;
						RI expectedRIs[numRisExpected] = {
							RI(STEP1COLOUR, 1),
							RI(SLIDERCOLOUR, 2),
							RI(STEP1COLOUR, 1),
							RI(STEP2COLOUR, 1),
							RI(STEP3COLOUR, 1),
							RI(STEP4COLOUR, 1),
							RI(BACKGROUNDCOLOUR, 3)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenHeadTail50PercentComplex1Step5_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 10);
						SliderAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 4, &output);

						// assert
						const int numRisExpected = 9;
						RI expectedRIs[numRisExpected] = {
							RI(STEP4COLOUR, 1),
							RI(STEP3COLOUR, 1),
							RI(STEP2COLOUR, 1),
							RI(STEP1COLOUR, 1),
							RI(SLIDERCOLOUR, 2),
							RI(STEP1COLOUR, 1),
							RI(STEP2COLOUR, 1),
							RI(STEP3COLOUR, 1),
							RI(STEP4COLOUR, 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenHeadTail50PercentComplex1Step8_RIsSet)
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
							RI(BACKGROUNDCOLOUR, 3),
							RI(STEP4COLOUR, 1),
							RI(STEP3COLOUR, 1),
							RI(STEP2COLOUR, 1),
							RI(STEP1COLOUR, 1),
							RI(SLIDERCOLOUR, 2),
							RI(STEP1COLOUR, 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenHeadTail50PercentComplex1Step9_RIsSet)
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
							RI(BACKGROUNDCOLOUR, 4),
							RI(STEP4COLOUR, 1),
							RI(STEP3COLOUR, 1),
							RI(STEP2COLOUR, 1),
							RI(STEP1COLOUR, 1),
							RI(SLIDERCOLOUR, 2)
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