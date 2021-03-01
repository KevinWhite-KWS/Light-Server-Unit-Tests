#include "CppUnitTest.h"

#include "..\LpiExecutor_Tester.h"
#include "..\..\..\..\..\Light-Server\src\LPE\LpiExecutors\AnimatedLpiExecutors\RainbowAnimatedLpiExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace LS::LPE::LpiExecutors;

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			namespace Rainbow {
				TEST_CLASS(ValidateLpi)
				{
				public:
					TEST_METHOD(WhenValidFadeLpi_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C003FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenVLengthIs0_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("07010000003C003FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenVLengthIs1_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("07010000013C003FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenVLengthIs255_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("07010000FF3C003FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenStepIs0_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A00003FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenStepIs1_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A01003FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenStepIs255_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000AFF003FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenStartNearIs2_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C203FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenStartNearIs9_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C203FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenStartNearIs1_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C103FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenNumberOfColoursIs0_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C100");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenNumberOfColoursIs11_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C10BAAAAAABBBBBBCCCCCCDDDDDDEEEEEEFFFFFFAAAAAABBBBBBCCCCCCDDDDDDEEEEEE");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenNumberOfColoursIs1_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C101AAAAAA");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenNumberOfColoursIs2_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C102AAAAAABBBBBB");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenNumberOfColoursIs10_TrueReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C10AAAAAAABBBBBBCCCCCCDDDDDDEEEEEEFFFFFFAAAAAABBBBBBCCCCCCDDDDDD");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsTrue(lpiIsValid);
					}

					TEST_METHOD(WhenMissing3rdColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C003FF000000FF000");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenMissing2ndColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C003FF0000");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}

					TEST_METHOD(WhenMissing1stColour_FalseReturned)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C003");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						bool lpiIsValid = lpiExecutor.ValidateLpi(tester.GetExecutorParams());

						// assert
						Assert::IsFalse(lpiIsValid);
					}
				};

				TEST_CLASS(GetNumberOfSteps)
				{
				public:
					TEST_METHOD(WhenEffectStepsIs60_StepsAre61)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A3C003FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(61, steps);
					}

					TEST_METHOD(WhenEffectStepsIs30_StepsAre31)
					{
						// arrange
						LpiExecutor_Tester tester("070100000A1E003FF000000FF000000FF");
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						uint16_t steps = lpiExecutor.GetNumberOfSteps(tester.GetExecutorParams());

						// assert
						Assert::AreEqual<int>(31, steps);
					}
				};

				TEST_CLASS(Execute)
				{
				public:
					TEST_METHOD(WhenNullOutput_Return)
					{
						// arrange
						RainbowAnimatedLpiExecutor lpiExecutor;

						// act
						lpiExecutor.Execute(nullptr, 0, nullptr);

						// assert
					}
				};
			}
		}
	}
}