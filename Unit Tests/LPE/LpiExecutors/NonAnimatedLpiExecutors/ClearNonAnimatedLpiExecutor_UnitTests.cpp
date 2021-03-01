#include "CppUnitTest.h"

#include "..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\NonAnimatedLpiExecutors\ClearNonAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Clear {
				TEST_CLASS(ValidateLpi)
				{
				public:
					TEST_METHOD(WhenValidate_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("00010000");
						ClearNonAnimatedLpiExecutor lpiExecutor;

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
						ClearNonAnimatedLpiExecutor lpiExecutor;

						// act
						lpiExecutor.Execute(nullptr, 0, nullptr);

						// assert
					}

					TEST_METHOD(WhenValidParams_RIsSet)
					{
						// arrange
						LpiExecutor_Tester tester("00010000");
						ClearNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(nullptr, 0, &output);

						// assert
						const int numRisExpected = 1;
						RI expectedRIs[numRisExpected] = {
							RI(Colour(0,0,0), 1)
						};
						bool risSetAsExpected = tester.ValidateOutput(&output, expectedRIs, numRisExpected);
						Assert::IsTrue(risSetAsExpected);
					}

					TEST_METHOD(WhenValidParams_RIsRepeat)
					{
						// arrange
						LpiExecutor_Tester tester("00010000");
						ClearNonAnimatedLpiExecutor lpiExecutor;
						LpiExecutorOutput output;

						// act
						lpiExecutor.Execute(nullptr, 0, &output);

						// assert
						Assert::IsTrue(output.GetRepeatRenderingInstructions());
					}
				};
			}
		}
	}
}