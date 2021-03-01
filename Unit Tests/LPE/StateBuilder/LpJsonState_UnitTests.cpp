#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/LpJsonState.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace StateBuilder {
			TEST_CLASS(LpJsonState_GetLpJsonDoc)
			{
			public:
				TEST_METHOD(WhenClassInstantiated_IsNotNull)
				{
					// arrange
					LpJsonState lpJsonState;

					// act
					StaticJsonDocument<BUFFER_LP>* jsonDoc = lpJsonState.getLpJsonDoc();

					// assert
					Assert::IsNotNull(jsonDoc);
					Assert::AreEqual<int>(BUFFER_LP, jsonDoc->capacity());
				}
			};

			TEST_CLASS(LpJsonState_GetCurrentInstruction)
			{
			public:
				TEST_METHOD(WhenClassInstantiated_IsNull)
				{
					// arrange
					LpJsonState lpJsonState;

					// act
					Instruction* currentIns = lpJsonState.getCurrentInstruction();

					// assert
					Assert::IsNull(currentIns);
				}

				TEST_METHOD(WhenSetToIns_IsIns)
				{
					// arrange
					LpJsonState lpJsonState;
					RepeatInstruction repeatIns;

					// act
					lpJsonState.setCurrentInstruction(&repeatIns);
					Instruction* currentIns = lpJsonState.getCurrentInstruction();

					// assert
					Assert::IsTrue(&repeatIns == currentIns);
				}
			};

			TEST_CLASS(LpJsonState_AddInstruction)
			{
			public:
				TEST_METHOD(WhenAddRepeat_RepeatInstanceReturnedSameIterations)
				{
					// arrange
					LpJsonState lpJsonState;
					RepeatInstruction repeatIns;
					repeatIns.setNumberOfIterations(1000);
					repeatIns.setRemainingIterations(500);

					// act
					Instruction* newIns = lpJsonState.addInstruction(&repeatIns);

					// assert
					Assert::AreEqual<int>(1000, ((RepeatInstruction*)newIns)->getNumberOfIterations());
					Assert::AreEqual<int>(500, ((RepeatInstruction*)newIns)->getRemainingIterations());
				}

				TEST_METHOD(WhenAddRepeat_RepeatInstanceReturnedDifferentInstance)
				{
					// arrange
					LpJsonState lpJsonState;
					RepeatInstruction repeatIns;
					repeatIns.setNumberOfIterations(1000);
					repeatIns.setRemainingIterations(500);

					// act
					Instruction* newIns = lpJsonState.addInstruction(&repeatIns);

					// assert
					Assert::IsTrue(&repeatIns != newIns);
				}

				TEST_METHOD(WhenAddLp_LpHasSameString)
				{
					// arrange
					LpJsonState lpJsonState;
					LpInstruction lpIns;
					const char* lpi = "01010000FF0000";
					lpIns.setLpi(lpi);

					// act
					Instruction* newIns = lpJsonState.addInstruction(&lpIns);

					// assert
					Assert::IsTrue(((LpInstruction*)newIns)->getLpi() == lpi);
				}

				TEST_METHOD(WhenAddLp_LpInstanceReturnedDifferentInstance)
				{
					// arrange
					LpJsonState lpJsonState;
					LpInstruction lpIns;
					const char* lpi = "01010000FF0000";
					lpIns.setLpi(lpi);

					// act
					Instruction* newIns = lpJsonState.addInstruction(&lpIns);

					// assert
					Assert::IsTrue(&lpIns != newIns);
				}

				TEST_METHOD(WhenAddInsNull_NullReturned)
				{
					// arrange
					LpJsonState lpJsonState;

					// act
					Instruction* newIns = lpJsonState.addInstruction(nullptr);

					// assert
					Assert::IsNull(newIns);
				}

				TEST_METHOD(WhenAddGreaterRepeatsThanAvailable_NullReturned)
				{
					// arrange
					LpJsonState lpJsonState;
					RepeatInstruction repeatIns;
					repeatIns.setNumberOfIterations(1000);

					// act
					Instruction* newIns = nullptr;
					for (int i = 0; i < MAX_REPEATINSTRUCTIONS + 1; i++) {
						newIns = lpJsonState.addInstruction(&repeatIns);
					}

					// assert
					Assert::IsNull(newIns);
				}

				TEST_METHOD(WhenAddMaxRepeatsThanAvailable_NullNotReturned)
				{
					// arrange
					LpJsonState lpJsonState;
					RepeatInstruction repeatIns;
					repeatIns.setNumberOfIterations(1000);

					// act
					Instruction* newIns = nullptr;
					for (int i = 0; i < MAX_REPEATINSTRUCTIONS; i++) {
						newIns = lpJsonState.addInstruction(&repeatIns);
					}

					// assert
					Assert::IsNotNull(newIns);
				}

				TEST_METHOD(WhenAddGreaterLpsThanAvailable_NullReturned)
				{
					// arrange
					LpJsonState lpJsonState;
					LpInstruction lpIns;
					lpIns.setLpi("01010000FF0000");

					// act
					Instruction* newIns = nullptr;
					for (int i = 0; i < MAX_LPINSTRUCTIONS + 1; i++) {
						newIns = lpJsonState.addInstruction(&lpIns);
					}

					// assert
					Assert::IsNull(newIns);
				}

				TEST_METHOD(WhenAddMaxLpsThanAvailable_NullNotReturned)
				{
					// arrange
					LpJsonState lpJsonState;
					LpInstruction lpIns;
					lpIns.setLpi("01010000FF0000");

					// act
					Instruction* newIns = nullptr;
					for (int i = 0; i < MAX_LPINSTRUCTIONS; i++) {
						newIns = lpJsonState.addInstruction(&lpIns);
					}

					// assert
					Assert::IsNotNull(newIns);
				}
			};

			TEST_CLASS(LpJsonState_GetFirstInstruction)
			{
			public:
				TEST_METHOD(WhenNoInsAdded_NullReturned)
				{
					// arrange
					LpJsonState lpJsonState;

					// act
					Instruction* firstIns = lpJsonState.getFirstInstruction();

					// assert
					Assert::IsNull(firstIns);
				}

				TEST_METHOD(WhenAddOneIns_FirstInsReturned)
				{
					// arrange
					LpJsonState lpJsonState;
					RepeatInstruction repeatIns;
					repeatIns.setNumberOfIterations(1000);
					lpJsonState.addInstruction(&repeatIns);

					// act
					Instruction* firstIns = lpJsonState.getFirstInstruction();

					// assert
					Assert::AreEqual<int>(1000, ((RepeatInstruction*)firstIns)->getNumberOfIterations());
				}

				TEST_METHOD(WhenAddTwoIns_FirstInsReturned)
				{
					// arrange
					LpJsonState lpJsonState;
					RepeatInstruction repeatIns;
					repeatIns.setNumberOfIterations(1000);
					lpJsonState.addInstruction(&repeatIns);
					repeatIns.setNumberOfIterations(500);
					lpJsonState.addInstruction(&repeatIns);

					// act
					Instruction* firstIns = lpJsonState.getFirstInstruction();

					// assert
					Assert::AreEqual<int>(1000, ((RepeatInstruction*)firstIns)->getNumberOfIterations());
				}
			};

			TEST_CLASS(LpJsonState_Reset)
			{
			public:
				TEST_METHOD(AfterInstantiate_CurrentInsIsNull)
				{
					// arrange
					LpJsonState lpJsonState;
					RepeatInstruction repeatIns;
					lpJsonState.addInstruction(&repeatIns);

					// act
					lpJsonState.reset();
					Instruction* currentIns = lpJsonState.getCurrentInstruction();

					// assert
					Assert::IsNull(currentIns);
				}

				TEST_METHOD(AfterInstantiate_FirstInsIsNull)
				{
					// arrange
					LpJsonState lpJsonState;
					RepeatInstruction repeatIns;
					lpJsonState.addInstruction(&repeatIns);

					// act
					lpJsonState.reset();
					Instruction* firstIns = lpJsonState.getFirstInstruction();

					// assert
					Assert::IsNull(firstIns);
				}
			};
		}
	}
}