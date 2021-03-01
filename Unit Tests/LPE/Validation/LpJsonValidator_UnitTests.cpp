#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/Validation/LpJsonValidator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace Validation {
			TEST_CLASS(LpJsonValidator_ValidateLp)
			{
			public:
				TEST_METHOD(WhenNullLp_NoInstructionsReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonValidator validator = LpJsonValidator(&validatorFactory);
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					validator.ValidateLp(nullptr, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::NoIntructions, (int)result.GetCode());
				}

				TEST_METHOD(WhenMissingName_MissingMandatoryPropertiesReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					LpJsonValidator validator = LpJsonValidator(&validatorFactory);
					FixedSizeCharBuffer lp = FixedSizeCharBuffer(1000);
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);
lp.LoadFromBuffer(
"{\
	\"instructions\" : [\
		\"00010000\"\
	]\
}"
);

					// act
					validator.ValidateLp(&lp, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::MissingMandatoryProperties, (int)result.GetCode());
				}

				TEST_METHOD(WhenMissingInstructions_NoInstructionsReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					LpJsonValidator validator = LpJsonValidator(&validatorFactory);
					FixedSizeCharBuffer lp = FixedSizeCharBuffer(1000);
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);
lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\"\
}"
);

					// act
					validator.ValidateLp(&lp, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::NoIntructions, (int)result.GetCode());
				}

				TEST_METHOD(WhenInvalidInstruction_InvalidInstructionReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					LpJsonValidator validator = LpJsonValidator(&validatorFactory);
					FixedSizeCharBuffer lp = FixedSizeCharBuffer(1000);
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);
lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		\"01010000\"\
	]\
}");

					// act
					validator.ValidateLp(&lp, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}

				TEST_METHOD(WhenNoInstructionsInRepeat_NoInstructionsInLoopReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					LpJsonValidator validator = LpJsonValidator(&validatorFactory);
					FixedSizeCharBuffer lp = FixedSizeCharBuffer(1000);
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);
lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 2\
			}\
		}\
	]\
}");

					// act
					validator.ValidateLp(&lp, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::NoInstructionsInLoop, (int)result.GetCode());
				}

				TEST_METHOD(WhenTwoInfiniteLoops_OnlyOneInfiniteLoopAllowedReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					LpJsonValidator validator = LpJsonValidator(&validatorFactory);
					FixedSizeCharBuffer lp = FixedSizeCharBuffer(1000);
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);
lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 0,\
				\"instructions\" : [\
					\"00010000\"\
				]\
			}\
		},\
		{\
			\"repeat\" : {\
				\"times\" : 0,\
				\"instructions\" : [\
					\"00010000\"\
				]\
			}\
		}\
	]\
}");

					// act
					validator.ValidateLp(&lp, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::OnlyOneInfiniteLoopAllowed, (int)result.GetCode());
				}

				TEST_METHOD(WhenNoInstructionsInRepeatInRepeat_NoInstructionsInLoopReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					LpJsonValidator validator = LpJsonValidator(&validatorFactory);
					FixedSizeCharBuffer lp = FixedSizeCharBuffer(1000);
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\":[\
					{\
						\"repeat\" : {\
							\"times\" : 3\
						}\
					}\
				]\
			}\
		}\
	]\
}");

					// act
					validator.ValidateLp(&lp, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::NoInstructionsInLoop, (int)result.GetCode());
				}

				TEST_METHOD(WhenMalformedJson_MissingMandatoryPropertiesReturn)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					LpJsonValidator validator = LpJsonValidator(&validatorFactory);
					FixedSizeCharBuffer lp = FixedSizeCharBuffer(1000);
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);
					lp.LoadFromBuffer(
"{\
	\"name : \"testing\",\
	\"instructions\" : [\
		\"00010000\"\
	]\
}");

					// act
					validator.ValidateLp(&lp, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::MissingMandatoryProperties, (int)result.GetCode());
				}

				TEST_METHOD(WhenMultipleValidLpis_ValidReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					LpJsonValidator validator = LpJsonValidator(&validatorFactory);
					FixedSizeCharBuffer lp = FixedSizeCharBuffer(1000);
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"Testing\",\
	\"instructions\" : [\
		\"00010000\",\
		\"01010000FF0000\",\
		\"0201000003010201FF000000FF000000FF\"\
	]\
}"
);

					// act
					validator.ValidateLp(&lp, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenMultipleRepeats_ValidReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					StringProcessor stringProcessor;
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionValidatorFactory validatorFactory = JsonInstructionValidatorFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					LpJsonValidator validator = LpJsonValidator(&validatorFactory);
					FixedSizeCharBuffer lp = FixedSizeCharBuffer(1000);
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);
					lp.LoadFromBuffer(
"{\
	\"name\" : \"Testing\",\
	\"instructions\" : [\
		{\
			\"repeat\" : {\
				\"times\" : 2,\
				\"instructions\": [\
					{\
						\"repeat\" : {\
							\"times\": 3,\
							\"instructions\" : [\
								\"00010000\",\
								\"01010000FF0000\"\
							]\
						}\
					}\
				]\
			}\
		},\
		\"01010000FFFFFF\"\
	]\
}"
);

					// act
					validator.ValidateLp(&lp, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}
			};
		}
	}
}