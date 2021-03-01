#include "CppUnitTest.h"

#include "..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\NonAnimatedLpiExecutors\PatternNonAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Pattern {
				TEST_CLASS(ValidateLpi)
				{
				public:
					TEST_METHOD(WhenNullParams_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("02010000020101FFFFFF000000");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(nullptr);

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenValidTwoColourPattern_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("02010000020101FFFFFF000000");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenNoIns_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("02010000");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenInvalidNumberOfBlocks_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("02010000-*");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenInvalidBlockWidth_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0201000002*-");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenMissingBlockWidth_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("020100000201");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenMissingColours_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("02010000020101");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenMissingColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("02010000020101FFFFFF");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenInvalidColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("02010000020101FFFFFF******");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenBlockWidthIs0_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("02010000020001FFFFFF000000");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenBlockWidthInvalidHex_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0201000002GG01FFFFFF000000");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenValidOneBlockPattern_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0201000001FF00FF");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenValidThreeBlockPattern_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0201000003050305FF00FF000000AAAAAA");
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}
				};

				TEST_CLASS(Execute)
				{
				public:
					TEST_METHOD(WhenNullOutput_Return)
					{
						// arrange
						PatternNonAnimatedLpiExecutor lpiExecutor;

						// act
						lpiExecutor.Execute(nullptr, 0, nullptr);

						// assert
					}

					TEST_METHOD(WhenSingleColour_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("020100000101FFFFFF");
						PatternNonAnimatedLpiExecutor lpiExecutor;
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

					TEST_METHOD(WhenSingleColour_RIsRepeat)
					{
						// arrange
						LpiExecutor_Tester tester("020100000101FFFFFF");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::IsTrue(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenSingleColour_OneRISet)
					{
						// arrange
						LpiExecutor_Tester tester("020100000101FFFFFF");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::AreEqual<int>(1, output.GetNumberOfRenderingInstructions());
					}

					TEST_METHOD(WhenTwoColour_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("02010000020101FFFFFF000000");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 2;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,255,255), 1),
							RI(Colour(0,0,0), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenTwoColour_RIsRepeat)
					{
						// arrange
						LpiExecutor_Tester tester("02010000020101FFFFFF000000");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::IsTrue(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenTwoColour_TwoRIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("02010000020101FFFFFF000000");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::AreEqual<int>(2, output.GetNumberOfRenderingInstructions());
					}

					TEST_METHOD(WhenThreeColour_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0201000003010101FF000000FF000000FF");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0), 1),
							RI(Colour(0,255,0), 1),
							RI(Colour(0,0,255), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenThreeColour_RIsRepeat)
					{
						// arrange
						LpiExecutor_Tester tester("0201000003010101FF000000FF000000FF");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::IsTrue(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenThreeColour_ThreeRIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0201000003010101FF000000FF000000FF");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::AreEqual<int>(3, output.GetNumberOfRenderingInstructions());
					}

					TEST_METHOD(WhenThreeColourDifferentWidths_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0201000003050403FF000000FF000000FF");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0), 5),
							RI(Colour(0,255,0), 4),
							RI(Colour(0,0,255), 3)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenThreeColourDifferentWidths_RIsRepeat)
					{
						// arrange
						LpiExecutor_Tester tester("0201000003050403FF000000FF000000FF");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::IsTrue(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenThreeColourDifferentWidths_ThreeRIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0201000003050403FF000000FF000000FF");
						PatternNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::AreEqual<int>(3, output.GetNumberOfRenderingInstructions());
					}
				};
			}
		}
	}
}