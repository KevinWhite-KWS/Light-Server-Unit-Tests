#include "CppUnitTest.h"

#include "..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\NonAnimatedLpiExecutors\StochasticNonAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Stochastic {
				TEST_CLASS(GetNumberOfSteps) {
					TEST_METHOD(WhenCalled_Is1) {
						// arrange
						LpiExecutor_Tester tester("0501000002FFFFFF000000");
						StochasticNonAnimatedLpiExecutor lpiExecutor;

						// act
						int steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(1, steps);
					}
				};

				TEST_CLASS(ValidateLpi)
				{
				public:
					TEST_METHOD(WhenNumberOfColoursIsZero_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0501000000FFFFFF000000");
						StochasticNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenNumberOfColoursIsOne_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0501000001FFFFFF000000");
						StochasticNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenNumberOfColoursIsFiftyOne_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0501000033FFFFFF000000");
						StochasticNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenNumberOfColoursIsTwo_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0501000002FFFFFF000000");
						StochasticNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenMissingSecondColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0501000002FFFFFF");
						StochasticNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenMissingFirstColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0501000002");
						StochasticNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenThreeColours_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0501000003AAAAAABBBBBBCCCCCC");
						StochasticNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenSixColours_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("0501000006AAAAAABBBBBBCCCCCCDDDDDDEEEEEEFFFFFF");
						StochasticNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}
				};

				TEST_CLASS(Execute) {
				public:
					TEST_METHOD(WhenNullOutput_Return)
					{
						// arrange
						StochasticNonAnimatedLpiExecutor lpiExecutor;

						// act
						lpiExecutor.Execute(nullptr, 0, nullptr);

						// assert
					}

					TEST_METHOD(WhenTwoColours_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0501000002FFFFFF000000");
						StochasticNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::AreEqual<int>(8, output.GetNumberOfRenderingInstructions());
						RI* setRIs = output.GetRenderingInstructions();
						const int numColours = 2;
						RI expectedRIs[numColours] = {
							RI(Colour(0,0,0),1),
							RI(Colour(255,255,255),1)
						};
						for (int riCounter = 0; riCounter < 8; riCounter++) {
							RI setRi = setRIs[riCounter];
							
							bool riIsExpected = false;
							for (int i = 0; i < numColours; i++) {
								if (setRi == expectedRIs[i]) {
									riIsExpected = true;
								}
							}
							Assert::IsTrue(riIsExpected);
						}
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenThreeColours_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0501000003AAAAAABBBBBBCCCCCC");
						StochasticNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::AreEqual<int>(8, output.GetNumberOfRenderingInstructions());
						RI* setRIs = output.GetRenderingInstructions();
						const int numColours = 3;
						RI expectedRIs[numColours] = {
							RI(Colour(170,170,170),1),
							RI(Colour(187,187,187),1),
							RI(Colour(204,204,204),1),
						};
						for (int riCounter = 0; riCounter < 8; riCounter++) {
							RI setRi = setRIs[riCounter];

							bool riIsExpected = false;
							for (int i = 0; i < numColours; i++) {
								if (setRi == expectedRIs[i]) {
									riIsExpected = true;
								}
							}
							Assert::IsTrue(riIsExpected);
						}
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenSixColours_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0501000006AAAAAABBBBBBCCCCCCDDDDDDEEEEEEFFFFFF");
						StochasticNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::AreEqual<int>(8, output.GetNumberOfRenderingInstructions());
						RI* setRIs = output.GetRenderingInstructions();
						const int numColours = 6;
						RI expectedRIs[numColours] = {
							RI(Colour(170,170,170),1),
							RI(Colour(187,187,187),1),
							RI(Colour(204,204,204),1),
							RI(Colour(221,221,221),1),
							RI(Colour(238,238,238),1),
							RI(Colour(255,255,255),1)
						};
						for (int riCounter = 0; riCounter < 8; riCounter++) {
							RI setRi = setRIs[riCounter];

							bool riIsExpected = false;
							for (int i = 0; i < numColours; i++) {
								if (setRi == expectedRIs[i]) {
									riIsExpected = true;
								}
							}
							Assert::IsTrue(riIsExpected);
						}
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}

					TEST_METHOD(WhenSixColours50LEDs_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("0501000006AAAAAABBBBBBCCCCCCDDDDDDEEEEEEFFFFFF", 50);
						StochasticNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::AreEqual<int>(50, output.GetNumberOfRenderingInstructions());
						RI* setRIs = output.GetRenderingInstructions();
						const int numColours = 6;
						RI expectedRIs[numColours] = {
							RI(Colour(170,170,170),1),
							RI(Colour(187,187,187),1),
							RI(Colour(204,204,204),1),
							RI(Colour(221,221,221),1),
							RI(Colour(238,238,238),1),
							RI(Colour(255,255,255),1)
						};
						for (int riCounter = 0; riCounter < 50; riCounter++) {
							RI setRi = setRIs[riCounter];

							bool riIsExpected = false;
							for (int i = 0; i < numColours; i++) {
								if (setRi == expectedRIs[i]) {
									riIsExpected = true;
								}
							}
							Assert::IsTrue(riIsExpected);
						}
						Assert::IsFalse(output.GetRepeatRenderingInstructions());
					}
				};
			}
		}
	}
}