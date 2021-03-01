#include "CppUnitTest.h"

#include "..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\NonAnimatedLpiExecutors\BlocksNonAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Blocks {
				TEST_CLASS(ValidateLpi)
				{
				public:
					TEST_METHOD(WhenNullParams_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0601000003212221FF000000FF000000FF");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(nullptr);

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenValidIns_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0601000003212221FF000000FF000000FF");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenBlocksIs0_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0601000000212221FF000000FF000000FF");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenBlocksIs1_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0601000000164FFFFFF");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenBlocksIs11_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("060100000B090909090909090909090AAAAAAABBBBBBCCCCCCCCAAAAAAABBBBBBCCCCCCCCAAAAAAABBBBBBCCCCCCCCAAAAAAABBBBBB");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenBlocksIs10_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("060100000A0A0A0A0A0A0A0A0A0A0AAAAAAAABBBBBBCCCCCCCCAAAAAAABBBBBBCCCCCCCCAAAAAAABBBBBBCCCCCCCCAAAAAAA");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenOneBlockWidth101_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("06010000026502FFFFFF000000");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenOneBlockWidth0_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("06010000026400FFFFFF000000");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenSumBlocks50_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("06010000021919FFFFFF000000");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenSumBlocks99_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("06010000023231FFFFFF000000");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenSumBlocks101_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("06010000023233FFFFFF000000");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenMissingBlockColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("06010000023232FFFFFF");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenMissingTwoBlockColours_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("06010000023232");
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}
				};

				TEST_CLASS(Execute)
				{
				public:
					TEST_METHOD(WhenNullOutput_Return)
					{
						// arrange
						BlocksNonAnimatedLpiExecutor lpiExecutor;

						// act
						lpiExecutor.Execute(nullptr, 0, nullptr);

						// assert
					}

					TEST_METHOD(When3BlockPattern193219_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0601000003193219FF000000FF000000FF");
						BlocksNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0), 2),
							RI(Colour(0,255,0), 4),
							RI(Colour(0,0,255), 2)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(When2BlockPattern3232_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("06010000023232FF000000FF00");
						BlocksNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 2;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0), 4),
							RI(Colour(0,255,0), 4)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(When3BlockPattern212221_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0601000003212221FF000000FF00FF0000");
						BlocksNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0), 3),
							RI(Colour(0,255,0), 2),
							RI(Colour(255,0,0), 3)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(When5BlockPattern1717171708_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("06010000051717171708FF000000FF00FF000000FF00FF0000");
						BlocksNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 5;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0), 2),
							RI(Colour(0,255,0), 1),
							RI(Colour(255,0,0), 2),
							RI(Colour(0,255,0), 1),
							RI(Colour(255,0,0), 2)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(When3BlockPattern40170D_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("060100000340170DFF000000FF00FF0000");
						BlocksNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 3;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,0), 6),
							RI(Colour(0,255,0), 1),
							RI(Colour(255,0,0), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}
				};
			}
		}
	}
}