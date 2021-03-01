#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/Validation/RepeatJsonInstructionValidator.h"
#include "JsonructionValidatorTestingHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace Validation {
			TEST_CLASS(RepeatJsonInstructionValidator_Validate)
			{
			public:
				TEST_METHOD(WhenNullRepeatVar_InvalidInstructionReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					RepeatJsonInstructionValidator repeatInsValidator = RepeatJsonInstructionValidator();
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ { 'repeat' : { 'times' : -1, 'instructions' : [ '00010000' ] } } ] }");
					JsonVariant repeatVar = (*elementToValidate)["repeat"];
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					repeatInsValidator.Validate(nullptr, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}

				TEST_METHOD(WhenTimesNeg1_LoopHasInvalidTimesValueReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					RepeatJsonInstructionValidator repeatInsValidator = RepeatJsonInstructionValidator();
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ { 'repeat' : { 'times' : -1, 'instructions' : [ '00010000' ] } } ] }");
					JsonVariant repeatVar = (*elementToValidate)["repeat"];
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					repeatInsValidator.Validate(&repeatVar, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::LoopHasInvalidTimesValue, (int)result.GetCode());
				}

				TEST_METHOD(WhenTimes1001_LoopHasInvalidTimesValueReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					RepeatJsonInstructionValidator repeatInsValidator = RepeatJsonInstructionValidator();
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ { 'repeat' : { 'times' : 1001, 'instructions' : [ '00010000' ] } } ] }");
					JsonVariant repeatVar = (*elementToValidate)["repeat"];
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					repeatInsValidator.Validate(&repeatVar, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::LoopHasInvalidTimesValue, (int)result.GetCode());
				}

				TEST_METHOD(WhenTimes0_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					RepeatJsonInstructionValidator repeatInsValidator = RepeatJsonInstructionValidator();
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ { 'repeat' : { 'times' : 0, 'instructions' : [ '00010000' ] } } ] }");
					JsonVariant repeatVar = (*elementToValidate)["repeat"];
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					repeatInsValidator.Validate(&repeatVar, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenTimes1_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					RepeatJsonInstructionValidator repeatInsValidator = RepeatJsonInstructionValidator();
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ { 'repeat' : { 'times' : 1, 'instructions' : [ '00010000' ] } } ] }");
					JsonVariant repeatVar = (*elementToValidate)["repeat"];
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					repeatInsValidator.Validate(&repeatVar, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenTimes500_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					RepeatJsonInstructionValidator repeatInsValidator = RepeatJsonInstructionValidator();
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ { 'repeat' : { 'times' : 500, 'instructions' : [ '00010000' ] } } ] }");
					JsonVariant repeatVar = (*elementToValidate)["repeat"];
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					repeatInsValidator.Validate(&repeatVar, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenTimes1000_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					RepeatJsonInstructionValidator repeatInsValidator = RepeatJsonInstructionValidator();
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ { 'repeat' : { 'times' : 1000, 'instructions' : [ '00010000' ] } } ] }");
					JsonVariant repeatVar = (*elementToValidate)["repeat"];
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					repeatInsValidator.Validate(&repeatVar, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenNoInstructions_NoInstructionsInLoopReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					RepeatJsonInstructionValidator repeatInsValidator = RepeatJsonInstructionValidator();
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ { 'repeat' : { 'times' : 50, 'instructions' : [ ] } } ] }");
					JsonVariant repeatVar = (*elementToValidate)["repeat"];
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					repeatInsValidator.Validate(&repeatVar, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::NoInstructionsInLoop, (int)result.GetCode());
				}

				TEST_METHOD(WhenTimesAndTwoInstruction_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					RepeatJsonInstructionValidator repeatInsValidator = RepeatJsonInstructionValidator();
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ { 'repeat' : { 'times' : 5, 'instructions' : [ '00010000', '01010000FFFFFF' ] } } ] }");
					JsonVariant repeatVar = (*elementToValidate)["repeat"];
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					repeatInsValidator.Validate(&repeatVar, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}
			};
		}
	}
}