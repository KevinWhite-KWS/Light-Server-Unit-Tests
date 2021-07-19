#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/LpJsonInstructionBuilder.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/LpJsonState.h"
#include "../../../../Light-Server/src/LPE/LpiExecutors/LpiExecutorFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace StateBuilder {
			TEST_CLASS(LpJsonInstructionBuilder_BuildInstruction)
			{
			public:
				TEST_METHOD(WhenNullJsonVariant_NullReturned)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					LpJsonInstructionBuilder builder(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonState state;


					// act
					Instruction* newIns = builder.BuildInstruction(nullptr, &state);

					// assert
					Assert::IsNull(newIns);
				}

				TEST_METHOD(WhenNullState_NullReturned)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					LpJsonInstructionBuilder builder(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					JsonVariant var;

					// act
					Instruction* newIns = builder.BuildInstruction(&var, nullptr);

					// assert
					Assert::IsNull(newIns);
				}

				TEST_METHOD(WhenValidLpi_LpInstructionReturned)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					LpJsonInstructionBuilder builder(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					JsonVariant var;
					StaticJsonDocument<1000> jsonDoc;
					deserializeJson(jsonDoc, "{ \"test\" : \"01010000FFFFFF\" }");
					JsonVariant testVar = jsonDoc["test"];
					LpJsonState state;

					// act
					Instruction* newIns = builder.BuildInstruction(&testVar, &state);
					LpInstruction* lpIns = dynamic_cast<LpInstruction*>(newIns);

					// assert
					Assert::IsNotNull(lpIns);
				}

				TEST_METHOD(WhenValidLpi_LpInstructionContainsLpi)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					LpJsonInstructionBuilder builder(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					JsonVariant var;
					StaticJsonDocument<1000> jsonDoc;
					deserializeJson(jsonDoc, "{ \"test\" : \"01010000FFFFFF\" }");
					JsonVariant testVar = jsonDoc["test"];
					LpJsonState state;

					// act
					Instruction* newIns = builder.BuildInstruction(&testVar, &state);
					LpInstruction* lpIns = dynamic_cast<LpInstruction*>(newIns);

					// assert
					int areEqual = strcmp(lpIns->getLpi(), "01010000FFFFFF");
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(WhenValidLpi_DurationSet)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					LpJsonInstructionBuilder builder(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					JsonVariant var;
					StaticJsonDocument<1000> jsonDoc;
					deserializeJson(jsonDoc, "{ \"test\" : \"01050000FFFFFF\" }");
					JsonVariant testVar = jsonDoc["test"];
					LpJsonState state;

					// act
					Instruction* newIns = builder.BuildInstruction(&testVar, &state);
					LpInstruction* lpIns = dynamic_cast<LpInstruction*>(newIns);

					// assert
					Assert::AreEqual<int>(5, lpIns->GetDuration());
				}

				TEST_METHOD(WhenValidLpi_StepsSet)
				{
					// arrange
					LEDConfig ledConfig;
					ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					LpJsonInstructionBuilder builder(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					JsonVariant var;
					StaticJsonDocument<1000> jsonDoc;
					deserializeJson(jsonDoc, "{ \"test\" : \"01050000FFFFFF\" }");
					JsonVariant testVar = jsonDoc["test"];
					LpJsonState state;

					// act
					Instruction* newIns = builder.BuildInstruction(&testVar, &state);
					LpInstruction* lpIns = dynamic_cast<LpInstruction*>(newIns);

					// assert
					Assert::AreEqual<int>(1, lpIns->GetNumberOfSteps());
				}
			};
		}
	}
}