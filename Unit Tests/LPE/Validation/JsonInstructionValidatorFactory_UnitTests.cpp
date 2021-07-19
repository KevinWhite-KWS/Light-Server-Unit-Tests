#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/Validation/JsonInstructionValidatorFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace Validation {
			TEST_CLASS(JsonInstructionValidatorFactory_GetValidator)
			{
			public:
				TEST_METHOD(WhenLpiType_LpiValidatorReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig();ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					// act
					IJsonInstructionValidator* validator = validatorFactory.GetValidator(InstructionType::Lpi);
					LpiJsonInstructionValidator* lpiValidator = dynamic_cast<LpiJsonInstructionValidator*>(validator);

					// assert
					Assert::IsNotNull(lpiValidator);
				}

				TEST_METHOD(WhenRepeatType_RepeatValidatorReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig();ledConfig.numberOfLEDs = 8;
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					// act
					IJsonInstructionValidator* validator = validatorFactory.GetValidator(InstructionType::Repeat);
					RepeatJsonInstructionValidator* repeatValidator = dynamic_cast<RepeatJsonInstructionValidator*>(validator);

					// assert
					Assert::IsNotNull(repeatValidator);
				}
			};
		}
	}
}