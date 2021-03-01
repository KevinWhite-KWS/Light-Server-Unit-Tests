#include "CppUnitTest.h"

#include "..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\NonAnimatedLpiExecutors\SolidNonAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Solid {
				TEST_CLASS(GetNumberOfSteps) {
					TEST_METHOD(WhenCalled_Is1) {
						// arrange
						LpiExecutor_Tester tester("01010000");
						SolidNonAnimatedLpiExecutor lpiExecutor;

						// act
						int steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(1, steps);
					}
				};

				TEST_CLASS(ValidateLpi)
				{
				public:
					TEST_METHOD(WhenNoColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("01010000");
						SolidNonAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenColour_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("01010000FF00FF");
						SolidNonAnimatedLpiExecutor lpiExecutor;

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
						SolidNonAnimatedLpiExecutor lpiExecutor;

						// act
						lpiExecutor.Execute(nullptr, 0, nullptr);

						// assert
					}

					TEST_METHOD(WhenColourSpecified_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("01010000FF00FF");
						SolidNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(255,0,255), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenColourSpecified_RIsRepeat)
					{
						// arrange
						LpiExecutor_Tester tester("01010000FF00FF");
						SolidNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(tester.GetExecutorParams(), 0, &output);

						// assert
						Assert::IsTrue(output.GetRepeatRenderingInstructions());
					}
				};
			}
		}
	}
}