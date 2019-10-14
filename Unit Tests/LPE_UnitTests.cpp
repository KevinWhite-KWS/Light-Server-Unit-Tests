#include "CppUnitTest.h"
#include "..\..\Light Server\src\LPE.h"
#include "..\mocks\Mock_LPE.h"
#include "..\Helpers\LPE_UnitTestHelper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS
{
	namespace LightProgramExecutor {
		TEST_CLASS(GetLPI) {
		public:
			/*** ONE GROUP NEGATIVE TESTS ***/
			TEST_METHOD(Instruction00Requested_ClearInstanceReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);
				instructionBuffer.LoadFromBuffer("00010000");

				// act
				LPI* lpi = lpe.GetLPI(&instructionBuffer);

				// assert
				ClearNonAnimatedLPI* targetLpi = dynamic_cast<ClearNonAnimatedLPI*>(lpi);
				Assert::IsNotNull(targetLpi);
			}

			TEST_METHOD(Instruction01Requested_SolidInstanceReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);
				instructionBuffer.LoadFromBuffer("01010000FFFFFF");

				// act
				LPI* lpi = lpe.GetLPI(&instructionBuffer);

				// assert
				SolidNonAnimatedLPI* targetLpi = dynamic_cast<SolidNonAnimatedLPI*>(lpi);
				Assert::IsNotNull(targetLpi);
			}

			TEST_METHOD(Instruction02Requested_PatternInstanceReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);
				instructionBuffer.LoadFromBuffer("0201000002010200FF00FF0000");

				// act
				LPI* lpi = lpe.GetLPI(&instructionBuffer);

				// assert
				PatternNonAnimatedLPI* targetLpi = dynamic_cast<PatternNonAnimatedLPI*>(lpi);
				Assert::IsNotNull(targetLpi);
			}

			TEST_METHOD(Instruction03Requested_SliderInstanceReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);
				instructionBuffer.LoadFromBuffer("03010000020FF000000FF00");

				// act
				LPI* lpi = lpe.GetLPI(&instructionBuffer);

				// assert
				SliderAnimatedLPI* targetLpi = dynamic_cast<SliderAnimatedLPI*>(lpi);
				Assert::IsNotNull(targetLpi);
			}

			TEST_METHOD(Instruction04Requested_FadeInstanceReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);
				instructionBuffer.LoadFromBuffer("04010000320000000FFFFFF");

				// act
				LPI* lpi = lpe.GetLPI(&instructionBuffer);

				// assert
				FadeAnimatedLPI* targetLpi = dynamic_cast<FadeAnimatedLPI*>(lpi);
				Assert::IsNotNull(targetLpi);
			}

			TEST_METHOD(Instruction05Requested_StochasticInstanceReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);
				instructionBuffer.LoadFromBuffer("0501000002FF000000FF00");

				// act
				LPI* lpi = lpe.GetLPI(&instructionBuffer);

				// assert
				StochasticNonAnimatedLPI* targetLpi = dynamic_cast<StochasticNonAnimatedLPI*>(lpi);
				Assert::IsNotNull(targetLpi);
			}

			TEST_METHOD(Instruction06Requested_BlocksInstanceReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);
				instructionBuffer.LoadFromBuffer("0601000003212221FF000000FF000000FF");

				// act
				LPI* lpi = lpe.GetLPI(&instructionBuffer);

				// assert

				BlocksNonAnimatedLPI* targetLpi = dynamic_cast<BlocksNonAnimatedLPI*>(lpi);
				Assert::IsNotNull(targetLpi);
			}

			TEST_METHOD(Instruction99Requested_NullptrReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);
				instructionBuffer.LoadFromBuffer("99010000");

				// act
				LPI* lpi = lpe.GetLPI(&instructionBuffer);

				// assert
				Assert::IsNull(lpi);
			}

			TEST_METHOD(InstructionIsNull_NullptrReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);
				instructionBuffer.LoadFromBuffer("99010000");

				// act
				LPI* lpi = lpe.GetLPI(nullptr);

				// assert
				Assert::IsNull(lpi);
			}

			TEST_METHOD(InstructionIsEmpty_NullptrReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);

				// act
				LPI* lpi = lpe.GetLPI(&instructionBuffer);

				// assert
				Assert::IsNull(lpi);
			}

			TEST_METHOD(InstructionIsInvalid_NullptrReturned)
			{
				// arrange
				LEDConfig ledConfig = LEDConfig(8);
				StringProcessor stringProcessor = StringProcessor();
				Mock_LPE lpe = Mock_LPE(&ledConfig, &stringProcessor);
				FixedSizeCharBuffer instructionBuffer = FixedSizeCharBuffer(1000);
				instructionBuffer.LoadFromBuffer("000000");

				// act
				LPI* lpi = lpe.GetLPI(&instructionBuffer);

				// assert
				Assert::IsNull(lpi);
			}
		};

		TEST_CLASS(ValidateLP) {
		public:
			TEST_METHOD(NullLP_NoExceptionExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(nullptr, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
			}

			TEST_METHOD(NullResult_NoExceptionExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);

				// act
				lpe->ValidateLP(&buffer, nullptr);

				// assert
				lpeUnitTestHelper.CleanUp();
			}

			TEST_METHOD(EmptyLP_MissingMandatoryPropertiesExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(MissingMandatoryProperties, result.GetCode());
			}

			TEST_METHOD(InvalidJSON_MissingMandatoryPropertiesExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("THISISNOTJSON");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(MissingMandatoryProperties, result.GetCode());
			}

			TEST_METHOD(EmptyNameProperty_MissingMandatoryPropertiesExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"\" }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(MissingMandatoryProperties, result.GetCode());
			}

			TEST_METHOD(MissingInstructionsProperty_NoIntructionsExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\" }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(NoIntructions, result.GetCode());
			}

			TEST_METHOD(EmptyInstructionsProperty_NoIntructionsExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : {} }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(NoIntructions, result.GetCode());
			}

			TEST_METHOD(OneValidInstruction_ValidExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"instruction\" : \"00010000\" } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(Valid, result.GetCode());
			}

			TEST_METHOD(OneInvalidInstruction_InvalidInstructionExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"instruction\" : \"ZZ000000\" } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				int areEqual = strcmp("ZZ000000", result.GetInfo());
				Assert::AreEqual<int>(InvalidInstruction, result.GetCode());
				Assert::AreEqual<int>(0, areEqual);
			}

			TEST_METHOD(ThreeValidInstructions_ValidExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"instruction\" : \"00010000\", \"instruction\" : \"0101000000FF00\", \"instruction\" : \"020500000301020100FF00FF000000FF00\" } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(Valid, result.GetCode());
			}

			TEST_METHOD(UnexpectedProperty_InvalidPropertyExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"instruction\" : \"00010000\", \"InvalidProperty\" : \"\" } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				int areEqual = strcmp("InvalidProperty", result.GetInfo());
				Assert::AreEqual<int>(InvalidProperty, result.GetCode());
				Assert::AreEqual<int>(0, areEqual);
			}

			TEST_METHOD(NoInstructionsInLoop_NoInstructionsInLoopExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"repeat\" : { \"times\" : 5 } } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(NoInstructionsInLoop, result.GetCode());
			}

			TEST_METHOD(NoInstructionsInNestedLoop_NoInstructionsInLoopExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\": { \"times\" : 5 } } } } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(NoInstructionsInLoop, result.GetCode());
			}

			TEST_METHOD(MissingTimesPropertyInLoop_MissingMandatoryPropertyExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"repeat\" : { \"instructions\" : {} } } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(MissingMandatoryProperties, result.GetCode());
			}

			TEST_METHOD(TimesPropertyInLoopInvalidChar_LoopHasInvalidTimesValue)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"instruction\" : \"00010000\", \"repeat\" : { \"times\": \"a\", \"instructions\" : {} } } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				int areEqual = strcmp("a", result.GetInfo());
				Assert::AreEqual<int>(LoopHasInvalidTimesValue, result.GetCode());
				Assert::AreEqual<int>(0, areEqual);
			}

			TEST_METHOD(TimesPropertyGreatMax_LoopHasInvalidTimesValue)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"instruction\" : \"00010000\", \"repeat\" : { \"times\": 1001, \"instructions\" : {} } } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				int areEqual = strcmp("1001", result.GetInfo());
				Assert::AreEqual<int>(LoopHasInvalidTimesValue, result.GetCode());
				Assert::AreEqual<int>(0, areEqual);
			}

			TEST_METHOD(TimesPropertyLessMin_LoopHasInvalidTimesValue)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"instruction\" : \"00100000\", \"repeat\" : { \"times\": -1, \"instructions\" : {} } } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				int areEqual = strcmp("-1", result.GetInfo());
				Assert::AreEqual<int>(LoopHasInvalidTimesValue, result.GetCode());
				Assert::AreEqual<int>(0, areEqual);
			}

			TEST_METHOD(MaxLoopValue_ValidExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"repeat\" : { \"times\" : 1000, \"instructions\" : { \"instruction\": \"00010000\" } } } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(Valid, result.GetCode());
			}

			TEST_METHOD(OneValidLoop_ValidExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\" } } } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(Valid, result.GetCode());
			}

			TEST_METHOD(TwoInfiniteLoops_OnlyOneInfiniteLoopAllowedExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"repeat\" : { \"times\" : 0, \"instructions\" :{ \"instruction\": \"00010000\", \"repeat\" : { \"times\" : 0, \"instructions\" : { \"instruction\" : \"00010000\" } } } } } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(OnlyOneInfiniteLoopAllowed, result.GetCode());
			}

			TEST_METHOD(TwoInfiniteLoopsSubsequent_OnlyOneInfiniteLoopAllowedExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\": \"My Program\", \"instructions\": { \"repeat\": { \"times\" : 0, \"instructions\" : { \"instruction\":\"00010000\" } }, \"repeat\": { \"times\" : 0, \"instructions\" : { \"instruction\":\"00010000\" } } } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(OnlyOneInfiniteLoopAllowed, result.GetCode());
			}

			TEST_METHOD(SixNestedLoops_Maximum5NestedLoopsAllowedExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00000000\" }} }} }} }} }} }} } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(Maximum5NestedLoopsAllowed, result.GetCode());
			}

			TEST_METHOD(FiveNestedLoops_ValidExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\" }} }} }} }} }} } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(Valid, result.GetCode());
			}

			TEST_METHOD(FiveNestedLoopsAndOneMore_ValidExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"00010000\" }} }} }} }} }}, \"repeat\": { \"times\": 5, \"instructions\": { \"instruction\": \"00010000\"  } }  } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(Valid, result.GetCode());
			}

			TEST_METHOD(TwoValidInstructionsOneInvalid_InvalidInstructionExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"instruction\" : \"00010000\", \"instruction\" : \"00010000\", \"instruction\" : \"000000\" } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				int areEqual = strcmp("000000", result.GetInfo());
				Assert::AreEqual<int>(InvalidInstruction, result.GetCode());
				Assert::AreEqual<int>(0, areEqual);
			}

			TEST_METHOD(OneClearOneLoopTwoInstructions_ValidExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"instruction\" : \"00010000\", \"repeat\":{ \"times\":5, \"instructions\":{ \"instruction\": \"01050000FF0000\", \"instruction\": \"0105000000FF00\" }  }  } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(Valid, result.GetCode());
			}

			TEST_METHOD(TwoNestedLoopsTwoInstructions_ValidExpected)
			{
				// arrange
				LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
				LPE* lpe = lpeUnitTestHelper.InstantiateLPE();
				FixedSizeCharBuffer buffer = FixedSizeCharBuffer(1000);
				buffer.LoadFromBuffer("{ \"name\" : \"My program\", \"instructions\" : { \"instruction\" : \"00010000\", \"repeat\": { \"times\":5, \"instructions\": { \"instruction\": \"01050000FF0000\", \"instruction\": \"0105000000FF00\", \"repeat\":{ \"times\":5, \"instructions\":{ \"instruction\": \"01050000FF0000\", \"instruction\": \"0105000000FF00\" }  } }  }  } }");
				LPValidateResult result = LPValidateResult();

				// act
				lpe->ValidateLP(&buffer, &result);

				// assert
				lpeUnitTestHelper.CleanUp();
				Assert::AreEqual<int>(Valid, result.GetCode());
			}
		};
	}
}