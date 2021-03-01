#include "CppUnitTest.h"

#include "..\..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\AnimatedLpiExecutors\RainbowAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

#define LPI		"070100000A3C103FF000000FF000000FF"

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Rainbow_3Colours60Steps10LengthStartFar {
				TEST_CLASS(Execute)
				{
				public:
					TEST_METHOD(WhenStep1_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 19);
						RainbowAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 19;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0),1),
							RI(Colour(178,0,76),1),
							RI(Colour(102,0,153),1),
							RI(Colour(25,0,229),1),
							RI(Colour(0,50,204),1),
							RI(Colour(0,127,127),1),
							RI(Colour(0,204,51),1),
							RI(Colour(25,229,0),1),
							RI(Colour(101,153,0),1),
							RI(Colour(178,76,0),1),
							RI(Colour(255,0,0),1),
							RI(Colour(178,0,76),1),
							RI(Colour(102,0,153),1),
							RI(Colour(25,0,229),1),
							RI(Colour(0,50,204),1),
							RI(Colour(0,127,127),1),
							RI(Colour(0,204,51),1),
							RI(Colour(25,229,0),1),
							RI(Colour(101,153,0),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStep10_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 19);
						RainbowAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 9, &output);

						// assert
						const int numRisExpected = 19;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(140,0,114),1),
							RI(Colour(216,0,38),1),
							RI(Colour(216,0,38),1),
							RI(Colour(140,0,114),1),
							RI(Colour(63,0,191),1),
							RI(Colour(0,12,242),1),
							RI(Colour(0,89,165),1),
							RI(Colour(0,165,89),1),
							RI(Colour(0,242,12),1),
							RI(Colour(63,191,0),1),
							RI(Colour(140,114,0),1),
							RI(Colour(216,38,0),1),
							RI(Colour(216,0,38),1),
							RI(Colour(140,0,114),1),
							RI(Colour(63,0,191),1),
							RI(Colour(0,12,242),1),
							RI(Colour(0,89,165),1),
							RI(Colour(0,165,89),1),
							RI(Colour(0,242,12),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStep20_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 19);
						RainbowAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 19, &output);

						// assert
						const int numRisExpected = 19;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(12,0,242),1),
							RI(Colour(89,0,165),1),
							RI(Colour(165,0,89),1),
							RI(Colour(242,0,12),1),
							RI(Colour(191,0,63),1),
							RI(Colour(114,0,140),1),
							RI(Colour(38,0,216),1),
							RI(Colour(0,38,216),1),
							RI(Colour(0,114,140),1),
							RI(Colour(0,191,63),1),
							RI(Colour(12,242,0),1),
							RI(Colour(89,165,0),1),
							RI(Colour(165,89,0),1),
							RI(Colour(242,12,0),1),
							RI(Colour(191,0,63),1),
							RI(Colour(114,0,140),1),
							RI(Colour(38,0,216),1),
							RI(Colour(0,38,216),1),
							RI(Colour(0,114,140),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStep30_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 19);
						RainbowAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 29, &output);

						// assert
						const int numRisExpected = 19;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,114,140),1),
							RI(Colour(0,38,216),1),
							RI(Colour(38,0,216),1),
							RI(Colour(114,0,140),1),
							RI(Colour(191,0,63),1),
							RI(Colour(242,0,12),1),
							RI(Colour(165,0,89),1),
							RI(Colour(89,0,165),1),
							RI(Colour(12,0,242),1),
							RI(Colour(0,63,191),1),
							RI(Colour(0,140,114),1),
							RI(Colour(0,216,38),1),
							RI(Colour(38,216,0),1),
							RI(Colour(114,140,0),1),
							RI(Colour(191,63,0),1),
							RI(Colour(242,0,12),1),
							RI(Colour(165,0,89),1),
							RI(Colour(89,0,165),1),
							RI(Colour(12,0,242),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStep40_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 19);
						RainbowAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 39, &output);

						// assert
						const int numRisExpected = 19;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,242,12),1),
							RI(Colour(0,165,89),1),
							RI(Colour(0,89,165),1),
							RI(Colour(0,12,242),1),
							RI(Colour(63,0,191),1),
							RI(Colour(140,0,114),1),
							RI(Colour(216,0,38),1),
							RI(Colour(216,0,38),1),
							RI(Colour(140,0,114),1),
							RI(Colour(63,0,191),1),
							RI(Colour(0,12,242),1),
							RI(Colour(0,89,165),1),
							RI(Colour(0,165,89),1),
							RI(Colour(0,242,12),1),
							RI(Colour(63,191,0),1),
							RI(Colour(140,114,0),1),
							RI(Colour(216,38,0),1),
							RI(Colour(216,0,38),1),
							RI(Colour(140,0,114),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStep50_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 19);
						RainbowAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 49, &output);

						// assert
						const int numRisExpected = 19;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(114,140,0),1),
							RI(Colour(38,216,0),1),
							RI(Colour(0,216,38),1),
							RI(Colour(0,140,114),1),
							RI(Colour(0,63,191),1),
							RI(Colour(12,0,242),1),
							RI(Colour(89,0,165),1),
							RI(Colour(165,0,89),1),
							RI(Colour(242,0,12),1),
							RI(Colour(191,0,63),1),
							RI(Colour(114,0,140),1),
							RI(Colour(38,0,216),1),
							RI(Colour(0,38,216),1),
							RI(Colour(0,114,140),1),
							RI(Colour(0,191,63),1),
							RI(Colour(12,242,0),1),
							RI(Colour(89,165,0),1),
							RI(Colour(165,89,0),1),
							RI(Colour(242,12,0),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStep60_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 19);
						RainbowAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 59, &output);

						// assert
						const int numRisExpected = 19;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(242,12,0),1),
							RI(Colour(165,89,0),1),
							RI(Colour(89,165,0),1),
							RI(Colour(12,242,0),1),
							RI(Colour(0,191,63),1),
							RI(Colour(0,114,140),1),
							RI(Colour(0,38,216),1),
							RI(Colour(38,0,216),1),
							RI(Colour(114,0,140),1),
							RI(Colour(191,0,63),1),
							RI(Colour(242,0,12),1),
							RI(Colour(165,0,89),1),
							RI(Colour(89,0,165),1),
							RI(Colour(12,0,242),1),
							RI(Colour(0,63,191),1),
							RI(Colour(0,140,114),1),
							RI(Colour(0,216,38),1),
							RI(Colour(38,216,0),1),
							RI(Colour(114,140,0),1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenStep61_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester(LPI, 19);
						RainbowAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 60, &output);

						// assert
						const int numRisExpected = 19;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0),1),
							RI(Colour(178,76,0),1),
							RI(Colour(101,153,0),1),
							RI(Colour(25,229,0),1),
							RI(Colour(0,204,51),1),
							RI(Colour(0,127,127),1),
							RI(Colour(0,50,204),1),
							RI(Colour(25,0,229),1),
							RI(Colour(102,0,153),1),
							RI(Colour(178,0,76),1),
							RI(Colour(255,0,0),1),
							RI(Colour(178,0,76),1),
							RI(Colour(102,0,153),1),
							RI(Colour(25,0,229),1),
							RI(Colour(0,50,204),1),
							RI(Colour(0,127,127),1),
							RI(Colour(0,204,51),1),
							RI(Colour(25,229,0),1),
							RI(Colour(101,153,0),1)
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