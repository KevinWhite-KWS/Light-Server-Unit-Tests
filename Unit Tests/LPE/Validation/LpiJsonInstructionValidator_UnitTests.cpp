#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/Validation/LpiJsonInstructionValidator.h"
#include "JsonructionValidatorTestingHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace Validation {
			TEST_CLASS(LpiJsonInstructionValidator_Validate)
			{
			public:
				TEST_METHOD(WhenNoVariantToValidate_InvalidInstructionReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '00010000'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(nullptr, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}

				TEST_METHOD(WhenValidClear_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '00010000'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenInvalidClear_InvalidInstructionReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '00000000'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}

				TEST_METHOD(WhenValidSolid_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '01010000FF00FF'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenInvalidSolid_InvalidInstructionReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '01010000FF00'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}

				TEST_METHOD(WhenValidPattern_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '0201000003010201FF000000FF000000FF'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenInvalidPattern_InvalidInstructionReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '020100000301020100FF000000FF'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}

				TEST_METHOD(WhenValidSlider_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '03010000020FF000000FF00'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenInvalidSlider_InvalidInstructionReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '03010000020FF0000'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}

				TEST_METHOD(WhenInvalidFade_InvalidInstructionReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '040A0000000'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}

				TEST_METHOD(WhenValidFade_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '040100000A0000000FFFFFF'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenValidStochastic_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '0501000002FF0000000000'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenInvalidStochastic_InvalidInstructionReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '0501000002FF0000'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}

				TEST_METHOD(WhenInvalidBlocks_InvalidInstructionReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '0601000003212221FF000000FF00'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}

				TEST_METHOD(WhenValidBlocks_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '0601000003212221FF000000FF000000FF'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenValidRainbow_ValidReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '070100000A3C003FF000000FF000000FF'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::Valid, (int)result.GetCode());
				}

				TEST_METHOD(WhenInvalidRainbow_InvalidInstructionReturned)
				{
					// arrange
					InstructionValidatorTestingHelper testingHelper;
					LpiJsonInstructionValidator lpInsValidator = LpiJsonInstructionValidator(&testingHelper.lpiFactory, &testingHelper.stringProcessor, &testingHelper.ledConfig);
					JsonVariant* elementToValidate = testingHelper.GetJsonElementToValidate("{ 'instructions': [ '070100000A3C003FF000000FF00'] }");
					LPValidateResult result;
					result.ResetResult(LPValidateCode::Valid);

					// act
					lpInsValidator.Validate(elementToValidate, &result);

					// assert
					Assert::AreEqual<int>((int)LPValidateCode::InvalidInstruction, (int)result.GetCode());
				}
			};
		}
	}
}