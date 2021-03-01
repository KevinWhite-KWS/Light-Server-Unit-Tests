#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/JsonInstructionBuilderFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace StateBuilder {
			TEST_CLASS(JsonInstructionBuilerFactory_GetInstructionBuilder)
			{
			public:
				TEST_METHOD(WhenLpiType_LpiInstructionBuilderReturned)
				{
					// arrange
					LEDConfig ledConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory builderFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					// act
					IJsonInstructionBuilder* builder = builderFactory.GetInstructionBuilder(InstructionType::Lpi);
					LpJsonInstructionBuilder* lpiBuilder = dynamic_cast<LpJsonInstructionBuilder*>(builder);

					// assert
					Assert::IsNotNull(lpiBuilder);
				}

				TEST_METHOD(WhenRepeatType_RepeatInstructionBuilderReturned)
				{
					// arrange
					LEDConfig ledConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory builderFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					// act
					IJsonInstructionBuilder* builder = builderFactory.GetInstructionBuilder(InstructionType::Repeat);
					RepeatJsonInstructionBuilder* lpiBuilder = dynamic_cast<RepeatJsonInstructionBuilder*>(builder);

					// assert
					Assert::IsNotNull(lpiBuilder);
				}
			};
		}
	}
}