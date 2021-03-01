#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/RepeatJsonInstructionBuilder.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/LpJsonState.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace StateBuilder {
			TEST_CLASS(RepeatJsonInstructionBuilder_BuildInstruction)
			{
			public:
				TEST_METHOD(WhenNullJsonVariant_NullReturned)
				{
					// arrange
					RepeatJsonInstructionBuilder builder;
					LpJsonState state;

					// act
					Instruction* newIns = builder.BuildInstruction(nullptr, &state);

					// assert
					Assert::IsNull(newIns);
				}

				TEST_METHOD(WhenNullState_NullReturned)
				{
					// arrange
					RepeatJsonInstructionBuilder builder;
					JsonVariant var;

					// act
					Instruction* newIns = builder.BuildInstruction(&var, nullptr);

					// assert
					Assert::IsNull(newIns);
				}

				TEST_METHOD(WhenValidRepeat_RepeatInstructionReturned)
				{
					// arrange
					RepeatJsonInstructionBuilder builder;
					JsonVariant var;
					StaticJsonDocument<1000> jsonDoc;
					deserializeJson(jsonDoc, "{ \"repeat\" : { \"times\" : 1000, \"instructions\": [] } }");
					JsonVariant testVar = jsonDoc["repeat"];
					LpJsonState state;

					// act
					Instruction* newIns = builder.BuildInstruction(&testVar, &state);
					RepeatInstruction* repeatIns = dynamic_cast<RepeatInstruction*>(newIns);

					// assert
					Assert::IsNotNull(repeatIns);
				}

				TEST_METHOD(WhenValidRepeat_RepeatInstructionContainsNumberOfIterations)
				{
					// arrange
					RepeatJsonInstructionBuilder builder;
					JsonVariant var;
					StaticJsonDocument<1000> jsonDoc;
					deserializeJson(jsonDoc, "{ \"repeat\" : { \"times\" : 1000, \"instructions\": [] } }");
					JsonVariant testVar = jsonDoc["repeat"];
					LpJsonState state;

					// act
					Instruction* newIns = builder.BuildInstruction(&testVar, &state);
					RepeatInstruction* repeatIns = dynamic_cast<RepeatInstruction*>(newIns);

					// assert
					Assert::AreEqual<int>(1000, repeatIns->getNumberOfIterations());
				}
			};
		}
	}
}