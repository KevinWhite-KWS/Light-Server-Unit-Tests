#include "CppUnitTest.h"
#include "..\..\Light-Server\src\LPE.h"
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

		TEST_CLASS(GetNextRI) {
			public:
				TEST_METHOD(NoLPLoaded_FalseExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPE();

					// act
					bool result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(false, result);
				}

				TEST_METHOD(LPLoaded_TrueExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"00010000\" } }");

					// act
					bool result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
				}

				TEST_METHOD(InvalidLPLoaded_FalseExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"00000000\" } }");

					// act
					bool result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(false, result);
				}

				TEST_METHOD(LPSingleRunClearInstruction_ClearRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"00010000\" } }");

					// act
					bool result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(GetFrame5FromClearLP_5FramesTotal_ClearRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"00050000\" } }");

					// act
					bool result;
					for(int i = 0; i < 5; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(GetFrame6FromClearLP_5FramesTotal_FalseExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"00050000\" } }");

					// act
					bool result;
					for (int i = 0; i < 6; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}


					// assert
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(false, result);
				}

				TEST_METHOD(GetFrame2FromTwoInstructionsLP_SolidRedRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"0101000000FF00\",  \"instruction\":\"01010000FF0000\"} }");

					// act
					bool result;
					for (int i = 0; i < 2; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SolidRedInLoop5Iterations_FifthFrame_SolidRedRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"01010000FF0000\" } },  \"instruction\":\"00010000\"} }");

					// act
					bool result;
					for (int i = 0; i < 5; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat (1..1):
					ins: solid red
				ins: clear (****)

				This ensures that the instruction pointer is placed at the correct
				instruction (clear) when popping to the root instructions node.
				*/
				TEST_METHOD(SolidRedInLoop5Iteration_2ndFrame_ClearRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 1, \"instructions\" : { \"instruction\" : \"01010000FF0000\" } },  \"instruction\":\"00010000\"} }");

					// act
					bool result;
					for (int i = 0; i < 2; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				ins: solid red
				repeat (1..5):
					ins: solid green
				ins: solid blue (****)

				This test ensures that the instruction pointer points to the solid
				blue on execution of the 7th frame.  That is, popping from the repeat
				ensures that it pops to the instruction following the repeat.
				*/
				TEST_METHOD(ClearThenSolidRedInLoop5IterationThenClear_SeventhFrame_ClearRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"01010000FF0000\", \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"0101000000FF00\" } },  \"instruction\":\"010100000000FF\"} }");

					// act
					bool result;
					for (int i = 0; i < 7; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("0000FF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SolidRedInLoop5IterationThenSolidGreenThenClear_SeventhFrame_ClearRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"01010000FF0000\" } },  \"instruction\":\"0101000000FF00\", \"instruction\":\"00010000\"} }");

					// act
					bool result;
					for (int i = 0; i < 7; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(FiveLoopThenClearThenFiveLoopThenClear_12thFrame_ClearRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"01010000FF0000\" } },  \"instruction\":\"0101000000FF00\", \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"01010000FF0000\" } }, \"instruction\":\"00010000\"} }");

					// act
					bool result;
					for (int i = 0; i < 12; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SolidInstructionsInInfiniteLoop_1stFrame_SolidRedRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 0, \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"instruction\" : \"0101000000FF00\" } } } }");

					// act
					bool result;
					for (int i = 0; i < 1; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SolidInstructionsIn1Loop_2ndFrame_SolidGreenRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 1, \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"instruction\" : \"0101000000FF00\" } } } }");

					// act
					bool result;
					for (int i = 0; i < 2; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SolidInstructionsInInfiniteLoop_2ndFrame_SolidGreenRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 0, \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"instruction\" : \"0101000000FF00\" } } } }");

					// act
					bool result;
					for (int i = 0; i < 2; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SolidInstructionsInInfiniteLoop_3rdFrame_SolidRedRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 0, \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"instruction\" : \"0101000000FF00\" } } } }");

					// act
					bool result;
					for (int i = 0; i < 3; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SolidInstructionsInInfiniteLoop_6thFrame_SolidGreenRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 0, \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"instruction\" : \"0101000000FF00\" } } } }");

					// act
					bool result;
					for (int i = 0; i < 6; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:
				repeat (infinite):
					ins: solid red (****)
					ins: solid green

				This test ensures that each iteration around the infinite
				loop resets the reading of those instructions from the first
				instruction.  We are expected solid red after performing
				several iterations.
				*/
				TEST_METHOD(SolidInstructionsInInfiniteLoop_11thFrame_SolidRedRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 0, \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"instruction\" : \"0101000000FF00\" } } } }");

					// act
					bool result;
					for (int i = 0; i < 11; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SolidInstructionsInInfiniteLoop_20thFrame_SolidGreenRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 0, \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"instruction\" : \"0101000000FF00\" } } } }");

					// act
					bool result;
					for (int i = 0; i < 20; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SliderNearAnimated_Frame1_RedThenGreenRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"03010000020FF000000FF00\" } }");

					// act
					bool result;
					for (int i = 0; i < 1; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FF00000200FF0006", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SliderNearAnimated_Frame7_RedThenGreenRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"03010000020FF000000FF00\" } }");

					// act
					bool result;
					for (int i = 0; i < 7; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0006FF000002", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SliderNearAnimated5RenderingFrameDuration_Frame6_RedThenGreenRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"03050000020FF000000FF00\" } }");

					// act
					bool result;
					for (int i = 0; i < 6; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0001FF00000200FF0005", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SliderNearAnimated5RenderingFrameDuration_Frame11_RedThenGreenRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"03050000020FF000000FF00\" } }");

					// act
					bool result;
					for (int i = 0; i < 11; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0002FF00000200FF0004", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(SliderNearAnimated5RenderingFrameDuration_Frame35_RedThenGreenRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\":\"03050000020FF000000FF00\" } }");

					// act
					bool result;
					for (int i = 0; i < 35; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00FF0006FF000002", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(LoopInLook_Frame1_SolidRedRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\": 5, \"instructions\" : { \"instruction\" : \"01010000FF0000\",  \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"0101000000FF00\" } } } } } }");

					// act
					bool result;
					for (int i = 0; i < 1; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:
				repeat (1..5):
					ins: solid red
					repeat (1..5):
						ins: solid green

				This test ensures that nested loops function as expected.
				*/
				TEST_METHOD(LoopInLook_Frame2_SolidGreenRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"01010000FF0000\",  \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"0101000000FF00\" } } } } } }");

					// act
					bool result;
					for (int i = 0; i < 2; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:
				repeat (1..5):
					ins: solid red (****)
					repeat(1..5):
						ins: solid green

				We are checking here that the loop correctly 'pops' back to the
				the proceeding loop and expected instruction after executing
				6 frames.  So, we expect solid red once, then five solid green
				, and finally solid red as the result (7th frame).
				*/
				TEST_METHOD(LoopInLoop_Frame7_SolidRedRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"01010000FF0000\",  \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"0101000000FF00\" } } } } } }");

					// act
					bool result;
					for (int i = 0; i < 7; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:
				
				repeat (1...5):
					repeat(1...5):
						ins: solid green
				ins: clear (****)

				This test ensures that the loop pops up twice to the final clear instruction.
				*/
				TEST_METHOD(LoopInLoop_Frame26_ClearRIExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 5, \"instructions\" : { \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"0101000000FF00\" } } } }, \"instruction\":\"00010000\" } }");

					// act
					bool result;
					for (int i = 0; i < 26; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(LoopInLook_Frame31_FalseExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"01010000FF0000\",  \"repeat\": { \"times\" : 5, \"instructions\" : { \"instruction\" : \"0101000000FF00\" } } } } } }");

					// act
					bool result;
					for (int i = 0; i < 31; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(false, result);
				}

				TEST_METHOD(LoopThenAnotherLoop_Frame3_SolidRedExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 1, \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"instruction\" : \"0101000000FF00\" } }, \"repeat\": { \"times\" : 1, \"instructions\" : { \"instruction\" : \"01010000FF0000\" } } } }");

					// act
					bool result;
					for (int i = 0; i < 3; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:
				repeat (1..2):
					ins: solid white
					repeat(1..2):
						ins: solid red
						repeat(1..5):
							ins: solid green
							ins: solid blue
						ins: clear (****)

				We are checking that 'popping' from the 3rd loop places the
				execution pointer at the correct instruction within the collection
				of new instructions.
				*/
				TEST_METHOD(ThreeLoopsPopTests_Frame13_ClearExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 2, \"instructions\" : { \"instruction\" : \"01010000FFFFFF\", \"repeat\" : { \"times\": 2, \"instructions\": { \"instruction\": \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\" : \"0101000000FF00\", \"instruction\": \"010100000000FF\" } }, \"instruction\": \"00010000\"  } } } } } }");

					// act
					bool result;
					for (int i = 0; i < 13; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:
				repeat (1..2):
					ins: solid white (****)
					repeat(1..2):
						ins: solid red
						repeat(1..5):
							ins: solid green
							ins: solid blue
						ins: clear

				We are checking that 'popping' happens and places the
				execution pointer at the correct next instruction.
				*/
				TEST_METHOD(ThreeLoopsPopTests_Frame26_WhiteExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 2, \"instructions\" : { \"instruction\" : \"01010000FFFFFF\", \"repeat\" : { \"times\": 2, \"instructions\": { \"instruction\": \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\" : \"0101000000FF00\", \"instruction\": \"010100000000FF\" } }, \"instruction\": \"00010000\"  } } } } } }");

					// act
					bool result;
					for (int i = 0; i < 26; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("FFFFFF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:
				repeat (1..2):
					ins: solid white
					repeat(1..2):
						ins: solid red
						repeat(1..5):
							ins: solid green
							ins: solid blue
						ins: clear (****)

				We are checking that the execution pointer is placed
				at the last instruction (clear).
				*/
				TEST_METHOD(ThreeLoopsPopTests_Frame50_WhiteExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 2, \"instructions\" : { \"instruction\" : \"01010000FFFFFF\", \"repeat\" : { \"times\": 2, \"instructions\": { \"instruction\": \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\" : \"0101000000FF00\", \"instruction\": \"010100000000FF\" } }, \"instruction\": \"00010000\"  } } } } } }");

					// act
					bool result;
					for (int i = 0; i < 50; i++) result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:
				repeat (1..2):
					ins: solid white (****)
					repeat(1..2):
						ins: solid red
						repeat(1..5):
							ins: solid green
							ins: solid blue
						ins: clear

				We are checking that the program ends after all executions.
				*/
				TEST_METHOD(ThreeLoopsPopTests_Frame51_FalseExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 2, \"instructions\" : { \"instruction\" : \"01010000FFFFFF\", \"repeat\" : { \"times\": 2, \"instructions\": { \"instruction\": \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\" : \"0101000000FF00\", \"instruction\": \"010100000000FF\" } }, \"instruction\": \"00010000\"  } } } } } }");

					// act
					bool result;
					for (int i = 0; i < 51; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(false, result);
				}

				/*
				For the following program:
				repeat (1..2):
					ins: solid white (****)
					repeat(1..2):
						ins: solid red
						repeat(1..2):
							ins: solid green

				We are checking that 'popping' happens and moves the
				execution pointer right back at the solid white instruction
				of the fist loop after the 2nd lop has complete both iterations
				for the first time.
				*/
				TEST_METHOD(ThreeLoopsPopTests_Frame8_WhiteExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": { \"times\" : 2, \"instructions\" : { \"instruction\" : \"01010000FFFFFF\", \"repeat\" : { \"times\": 2, \"instructions\": { \"instruction\": \"01010000FF0000\", \"repeat\" : { \"times\" : 2, \"instructions\" : { \"instruction\" : \"0101000000FF00\" } } } } } } } }");

					// act
					bool result;
					for (int i = 0; i < 8; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("FFFFFF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				ins: solid red (****)
				repeat (1..1):
					ins: solid green
				ins: solid blue
				repeat
					ins: solid white
				ins: clear

				We expect the first instruction to be returned - solid red - when frame 1 is requested.
				*/
				TEST_METHOD(ThreeIns2Loops_Frame1_SolidRedExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"0101000000FF00\" } }, \"instruction\" : \"010100000000FF\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"01010000FFFFFF\" } }, \"instruction\" : \"00010000\" } }");

					// act
					bool result;
					for (int i = 0; i < 1; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				ins: solid red
				repeat (1..1):
					ins: solid green (****)
				ins: solid blue
				repeat
					ins: solid white
				ins: clear

				We expect the second instruction to be returned - solid green - when frame 1 is requested.
				This test ensures that the instruction pointer is positioned correctly when loops
				are popped.
				*/
				TEST_METHOD(ThreeIns2Loops_Frame2_SolidGreenExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"0101000000FF00\" } }, \"instruction\" : \"010100000000FF\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"01010000FFFFFF\" } }, \"instruction\" : \"00010000\" } }");

					// act
					bool result;
					for (int i = 0; i < 2; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				ins: solid red
				repeat (1..1):
					ins: solid green 
				ins: solid blue (****)
				repeat
					ins: solid white
				ins: clear

				We expect the third instruction to be returned - solid white - when frame 3 is requested.
				This test ensures that the instruction pointer is positioned correctly when loops
				are popped.
				*/
				TEST_METHOD(ThreeIns2Loops_Frame3_SolidBlueExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"0101000000FF00\" } }, \"instruction\" : \"010100000000FF\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"01010000FFFFFF\" } }, \"instruction\" : \"00010000\" } }");

					// act
					bool result;
					for (int i = 0; i < 3; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("0000FF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				ins: solid red
				repeat (1..1):
					ins: solid green
				ins: solid blue
				repeat
					ins: solid white (****)
				ins: clear

				We expect the fourth instruction to be returned - solid white - when frame 4 is requested.
				This test ensures that the instruction pointer is positioned correctly when loops
				are popped.
				*/
				TEST_METHOD(ThreeIns2Loops_Frame4_SolidWhiteExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"0101000000FF00\" } }, \"instruction\" : \"010100000000FF\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"01010000FFFFFF\" } }, \"instruction\" : \"00010000\" } }");

					// act
					bool result;
					for (int i = 0; i < 4; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("FFFFFF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				ins: solid red
				repeat (1..1):
					ins: solid green
				ins: solid blue
				repeat
					ins: solid white
				ins: clear (****)

				We expect the fifth instruction to be returned - clear - when frame 5 is requested.
				This test ensures that the instruction pointer is positioned correctly when loops
				are popped.
				*/
				TEST_METHOD(ThreeIns2Loops_Frame5_ClearExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"0101000000FF00\" } }, \"instruction\" : \"010100000000FF\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"01010000FFFFFF\" } }, \"instruction\" : \"00010000\" } }");

					// act
					bool result;
					for (int i = 0; i < 5; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				ins: solid red
				repeat (1..1):
					ins: solid green
				ins: solid blue
				repeat
					ins: solid white
				ins: clear

				We expect false to be returned when the 6th frame is requested (i.e. no further
				instructions).  This ensures that programs finishing executing when expected.
				*/
				TEST_METHOD(ThreeIns2Loops_Frame6_FalseExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"0101000000FF00\" } }, \"instruction\" : \"010100000000FF\", \"repeat\" : { \"times\" : 1, \"instructions\" : { \"instruction\": \"01010000FFFFFF\" } }, \"instruction\" : \"00010000\" } }");

					// act
					bool result;
					for (int i = 0; i < 6; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(false, result);
				}

				/*
				For the following program:

				repeat (1..5):
					ins: solid green
					ins: solid red
				ins: clear (***)
				repeat (1..5):
					ins: solid blue
					ins: solid white
				ins: clear
				repeat (1..5):
					ins: solid (FF,FF,00)
					ins: solid (00,FF,FF)

				We are ensuring that loop popping works after the expected
				number of iterations of that loop
				*/
				TEST_METHOD(ThreeLoops2Ins_Frame11_ClearExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"0101000000FF00\", \"instruction\": \"01010000FF0000\"  } }, \"instruction\" : \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"010100000000FF\", \"instruction\": \"01010000FFFFFF\"  } }, \"instruction\" : \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"01010000FFFF00\", \"instruction\": \"0101000000FFFF\"  } } } }");

					// act
					bool result;
					for (int i = 0; i < 11; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat (1..5):
					ins: solid green
					ins: solid red
				ins: clear 
				repeat (1..5):
					ins: solid blue
					ins: solid white (****)
				ins: clear
				repeat (1..5):
					ins: solid (FF,FF,00)
					ins: solid (00,FF,FF)

				We are ensuring that loop popping works after the expected
				number of iterations of that loop
				*/
				TEST_METHOD(ThreeLoops2Ins_Frame15_SolidWhiteExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"0101000000FF00\", \"instruction\": \"01010000FF0000\"  } }, \"instruction\" : \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"010100000000FF\", \"instruction\": \"01010000FFFFFF\"  } }, \"instruction\" : \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"01010000FFFF00\", \"instruction\": \"0101000000FFFF\"  } } } }");

					// act
					bool result;
					for (int i = 0; i < 15; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("FFFFFF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat (1..5):
					ins: solid green
					ins: solid red
				ins: clear
				repeat (1..5):
					ins: solid blue
					ins: solid white 
				ins: clear (****)
				repeat (1..5):
					ins: solid (FF,FF,00)
					ins: solid (00,FF,FF)

				We are ensuring that loop popping works and moves
				to the expected next instruction.
				*/
				TEST_METHOD(ThreeLoops2Ins_Frame22_ClearExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"0101000000FF00\", \"instruction\": \"01010000FF0000\"  } }, \"instruction\" : \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"010100000000FF\", \"instruction\": \"01010000FFFFFF\"  } }, \"instruction\" : \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"01010000FFFF00\", \"instruction\": \"0101000000FFFF\"  } } } }");

					// act
					bool result;
					for (int i = 0; i < 22; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat (1..5):
					ins: solid green
					ins: solid red
				ins: clear
				repeat (1..5):
					ins: solid blue
					ins: solid white
				ins: clear
				repeat (1..5):
					ins: solid (FF,FF,00) (****)
					ins: solid (00,FF,FF)

				We are ensuring that loop popping works after the expected
				and moves to the expected next instruction.
				*/
				TEST_METHOD(ThreeLoops2Ins_Frame25_FFFF00Expected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"0101000000FF00\", \"instruction\": \"01010000FF0000\"  } }, \"instruction\" : \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"010100000000FF\", \"instruction\": \"01010000FFFFFF\"  } }, \"instruction\" : \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"01010000FFFF00\", \"instruction\": \"0101000000FFFF\"  } } } }");

					// act
					bool result;
					for (int i = 0; i < 25; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("FFFF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat (1..5):
					ins: solid green
					ins: solid red
				ins: clear
				repeat (1..5):
					ins: solid blue
					ins: solid white
				ins: clear
				repeat (1..5):
					ins: solid (FF,FF,00) 
					ins: solid (00,FF,FF) (****)

				We are ensuring that loop popping works after the expected
				and moves to the expected next instruction.
				*/
				TEST_METHOD(ThreeLoops2Ins_Frame28_00FFFFExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"0101000000FF00\", \"instruction\": \"01010000FF0000\"  } }, \"instruction\" : \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"010100000000FF\", \"instruction\": \"01010000FFFFFF\"  } }, \"instruction\" : \"00010000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"instruction\": \"01010000FFFF00\", \"instruction\": \"0101000000FFFF\"  } } } }");

					// act
					bool result;
					for (int i = 0; i < 28; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						Logger::WriteMessage(lpeUnitTestHelper.riBuffer->GetBuffer());
					}

					// assert
					int areEqual = strcmp("00FFFF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat(1...5):
					ins: solid red
					repeat(1...5):
						repeat(1...2):
							ins:solid blue
					ins: solid green
					ins: solid white
				repeat(1....2):
					ins: solid (FF,FF,00)
				ins: clear

				We are ensuring that complex programs execute as expected.
				*/
				TEST_METHOD(TwoLoopsThreeNested_Frame1_SolidRedExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": {	\"times\": 5, \"instructions\": { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 2,	\"instructions\" : { \"instruction\" : \"010100000000FF\" } } }	}, \"instruction\" : \"0101000000FF00\", \"instruction\" : \"01010000FFFFFF\" } }, \"repeat\" : {	\"times\" : 2, \"instructions\" : { \"instruction\" : \"01010000FFFF00\" } }, \"instruction\" : \"00010000\" }}");

					// act
					bool result;
					for (int i = 0; i < 1; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat(1...5):
					ins: solid red
					repeat(1...5):
						repeat(1...2):
							ins:solid blue
					ins: solid green
					ins: solid white
				repeat(1....2):
					ins: solid (FF,FF,00) (each frame lasts 5 rendering frames)
				ins: clear

				We are ensuring that complex programs execute as expected.
				*/
				TEST_METHOD(TwoLoopsThreeNested_Frame2_SolidBlueExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": {	\"times\": 5, \"instructions\": { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 2,	\"instructions\" : { \"instruction\" : \"010100000000FF\" } } }	}, \"instruction\" : \"0101000000FF00\", \"instruction\" : \"01010000FFFFFF\" } }, \"repeat\" : {	\"times\" : 2, \"instructions\" : { \"instruction\" : \"01050000FFFF00\" } }, \"instruction\" : \"00010000\" }}");

					// act
					bool result;
					for (int i = 0; i < 2; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("0000FF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat(1...5):
					ins: solid red
					repeat(1...5):
						repeat(1...2):
							ins:solid blue
					ins: solid green
					ins: solid white
				repeat(1....2):
					ins: solid (FF,FF,00) (each frame lasts 5 rendering frames)
				ins: clear

				We are ensuring that complex programs execute as expected.
				*/
				TEST_METHOD(TwoLoopsThreeNested_Frame12_SolidGreenExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": {	\"times\": 5, \"instructions\": { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 2,	\"instructions\" : { \"instruction\" : \"010100000000FF\" } } }	}, \"instruction\" : \"0101000000FF00\", \"instruction\" : \"01010000FFFFFF\" } }, \"repeat\" : {	\"times\" : 2, \"instructions\" : { \"instruction\" : \"01050000FFFF00\" } }, \"instruction\" : \"00010000\" }}");

					// act
					bool result;
					for (int i = 0; i < 12; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("00FF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat(1...5):
					ins: solid red
					repeat(1...5):
						repeat(1...2):
							ins:solid blue
					ins: solid green
					ins: solid white
				repeat(1....2):
					ins: solid (FF,FF,00) (each frame lasts 5 rendering frames)
				ins: clear

				We are ensuring that complex programs execute as expected.
				*/
				TEST_METHOD(TwoLoopsThreeNested_Frame13_SolidWhiteExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": {	\"times\": 5, \"instructions\": { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 2,	\"instructions\" : { \"instruction\" : \"010100000000FF\" } } }	}, \"instruction\" : \"0101000000FF00\", \"instruction\" : \"01010000FFFFFF\" } }, \"repeat\" : {	\"times\" : 2, \"instructions\" : { \"instruction\" : \"01050000FFFF00\" } }, \"instruction\" : \"00010000\" }}");

					// act
					bool result;
					for (int i = 0; i < 13; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("FFFFFF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat(1...5):
					ins: solid red
					repeat(1...5):
						repeat(1...2):
							ins:solid blue
					ins: solid green
					ins: solid white
				repeat(1....2):
					ins: solid (FF,FF,00) (each frame lasts 5 rendering frames)
				ins: clear

				We are ensuring that complex programs execute as expected.
				*/
				TEST_METHOD(TwoLoopsThreeNested_Frame14_SolidRedExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": {	\"times\": 5, \"instructions\": { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 2,	\"instructions\" : { \"instruction\" : \"010100000000FF\" } } }	}, \"instruction\" : \"0101000000FF00\", \"instruction\" : \"01010000FFFFFF\" } }, \"repeat\" : {	\"times\" : 2, \"instructions\" : { \"instruction\" : \"01050000FFFF00\" } }, \"instruction\" : \"00010000\" }}");

					// act
					bool result;
					for (int i = 0; i < 14; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("FF000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat(1...5):
					ins: solid red
					repeat(1...5):
						repeat(1...2):
							ins:solid blue
					ins: solid green
					ins: solid white
				repeat(1....2):
					ins: solid (FF,FF,00) (each frame lasts 5 rendering frames)
				ins: clear

				We are ensuring that complex programs execute as expected.
				*/
				TEST_METHOD(TwoLoopsThreeNested_Frame65_SolidWhiteExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": {	\"times\": 5, \"instructions\": { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 2,	\"instructions\" : { \"instruction\" : \"010100000000FF\" } } }	}, \"instruction\" : \"0101000000FF00\", \"instruction\" : \"01010000FFFFFF\" } }, \"repeat\" : {	\"times\" : 2, \"instructions\" : { \"instruction\" : \"01050000FFFF00\" } }, \"instruction\" : \"00010000\" }}");

					// act
					bool result;
					for (int i = 0; i < 65; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("FFFFFF01R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat(1...5):
					ins: solid red
					repeat(1...5):
						repeat(1...2):
							ins:solid blue
					ins: solid green
					ins: solid white
				repeat(1....2):
					ins: solid (FF,FF,00) (each frame lasts 5 rendering frames)
				ins: clear

				We are ensuring that complex programs execute as expected.
				*/
				TEST_METHOD(TwoLoopsThreeNested_Frame66_SolidFFFF00Expected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": {	\"times\": 5, \"instructions\": { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 2,	\"instructions\" : { \"instruction\" : \"010100000000FF\" } } }	}, \"instruction\" : \"0101000000FF00\", \"instruction\" : \"01010000FFFFFF\" } }, \"repeat\" : {	\"times\" : 2, \"instructions\" : { \"instruction\" : \"01050000FFFF00\" } }, \"instruction\" : \"00010000\" }}");

					// act
					bool result;
					for (int i = 0; i < 66; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("FFFF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat(1...5):
					ins: solid red
					repeat(1...5):
						repeat(1...2):
							ins:solid blue
					ins: solid green
					ins: solid white
				repeat(1....2):
					ins: solid (FF,FF,00) (each frame lasts 5 rendering frames)
				ins: clear

				We are ensuring that complex programs execute as expected.
				*/
				TEST_METHOD(TwoLoopsThreeNested_Frame67_SolidFFFF00Expected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": {	\"times\": 5, \"instructions\": { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 2,	\"instructions\" : { \"instruction\" : \"010100000000FF\" } } }	}, \"instruction\" : \"0101000000FF00\", \"instruction\" : \"01010000FFFFFF\" } }, \"repeat\" : {	\"times\" : 2, \"instructions\" : { \"instruction\" : \"01050000FFFF00\" } }, \"instruction\" : \"00010000\" }}");

					// act
					bool result;
					for (int i = 0; i < 67; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("FFFF0001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat(1...5):
					ins: solid red
					repeat(1...5):
						repeat(1...2):
							ins:solid blue
					ins: solid green
					ins: solid white
				repeat(1....2):
					ins: solid (FF,FF,00) (each frame lasts 5 rendering frames)
				ins: clear

				We are ensuring that complex programs execute as expected.
				*/
				TEST_METHOD(TwoLoopsThreeNested_Frame76_ClearExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": {	\"times\": 5, \"instructions\": { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 2,	\"instructions\" : { \"instruction\" : \"010100000000FF\" } } }	}, \"instruction\" : \"0101000000FF00\", \"instruction\" : \"01010000FFFFFF\" } }, \"repeat\" : {	\"times\" : 2, \"instructions\" : { \"instruction\" : \"01050000FFFF00\" } }, \"instruction\" : \"00010000\" }}");

					// act
					bool result;
					for (int i = 0; i < 76; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("00000001R", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
				For the following program:

				repeat(1...5):
					ins: solid red
					repeat(1...5):
						repeat(1...2):
							ins:solid blue
					ins: solid green
					ins: solid white
				repeat(1....2):
					ins: solid (FF,FF,00) (each frame lasts 5 rendering frames)
				ins: clear

				We are ensuring that complex programs execute as expected.
				*/
				TEST_METHOD(TwoLoopsThreeNested_Frame77_FalseExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"my program\", \"instructions\" : { \"repeat\": {	\"times\": 5, \"instructions\": { \"instruction\" : \"01010000FF0000\", \"repeat\" : { \"times\" : 5, \"instructions\" : { \"repeat\" : { \"times\" : 2,	\"instructions\" : { \"instruction\" : \"010100000000FF\" } } }	}, \"instruction\" : \"0101000000FF00\", \"instruction\" : \"01010000FFFFFF\" } }, \"repeat\" : {	\"times\" : 2, \"instructions\" : { \"instruction\" : \"01050000FFFF00\" } }, \"instruction\" : \"00010000\" }}");

					// act
					bool result;
					for (int i = 0; i < 77; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(false, result);
				}

				/*
				For the following program:

				repeat (infinite):
					ins: fade black to red (5 frame duration)
					ins: fade red to black (5 frame duration)

				We are ensuring that the fade in / out works as expected
				*/
				TEST_METHOD(InfiniteFadeInFadeOut_Frame1_000000Expected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04050000320000000FFFFFF\", \"instruction\" : \"04050000321000000FFFFFF\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 1; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("00000008", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				/*
								For the following program:

								repeat (infinite):
									ins: fade black to red (5 frame duration)
									ins: fade red to black (5 frame duration)

								We are ensuring that the fade in / out works as expected
								*/
				TEST_METHOD(InfiniteFadeInFadeOut_Frame6_FFFFFFExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04050000320000000FFFFFF\", \"instruction\" : \"04050000321000000FFFFFF\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 6; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("32323208", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(InfiniteFadeInFadeOut_Frame30_FAFAFAExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04050000320000000FFFFFF\", \"instruction\" : \"04050000321000000FFFFFF\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 30; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("FAFAFA08", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(InfiniteFadeInFadeOut_Frame35_FFFFFFExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04050000320000000FFFFFF\", \"instruction\" : \"04050000321000000FFFFFF\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 35; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("FFFFFF08", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(InfiniteFadeInFadeOut_Frame41_CDCDCDExpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04050000320000000FFFFFF\", \"instruction\" : \"04050000321FFFFFF000000\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 41; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("CDCDCD08", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(InfiniteFadeInFadeOut_Frame51_696969xpected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04050000320000000FFFFFF\", \"instruction\" : \"04050000321FFFFFF000000\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 51; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("69696908", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(InfiniteFadeInFadeOut_Frame61_050505Expected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04050000320000000FFFFFF\", \"instruction\" : \"04050000321FFFFFF000000\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 61; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("05050508", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(InfiniteFadeInFadeOut_Frame66_000000Expected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04050000320000000FFFFFF\", \"instruction\" : \"04050000321FFFFFF000000\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 66; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("00000008", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(InfiniteFadeInFadeOut_Frame81_646464Expected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04050000320000000FFFFFF\", \"instruction\" : \"04050000321FFFFFF000000\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 81; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("64646408", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(InfiniteFadeOut_Frame1_FF0000Expected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04010000321FF0000000000\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 1; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("FF000008", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}

				TEST_METHOD(InfiniteFadeOut_Frame2_CD0000Expected)
				{
					// arrange
					LPE_UnitTestHelper lpeUnitTestHelper = LPE_UnitTestHelper();
					LPE* lpe = lpeUnitTestHelper.InstantiateLPEWithProgram("{ \"name\" : \"fade test\", \"instructions\" : { \"repeat\" : { \"times\": 0, \"instructions\" : { \"instruction\" : \"04010000321FF0000000000\" } }}}");

					// act
					bool result;
					for (int i = 0; i < 2; i++) {
						result = lpe->GetNextRI(lpeUnitTestHelper.riBuffer);
						std::stringstream ss;
						ss << i << ":" << lpeUnitTestHelper.riBuffer->GetBuffer();
						Logger::WriteMessage(ss.str().c_str());
					}

					// assert
					int areEqual = strcmp("CD000008", lpeUnitTestHelper.riBuffer->GetBuffer());
					lpeUnitTestHelper.CleanUp();
					Assert::AreEqual<bool>(true, result);
					Assert::AreEqual<int>(0, areEqual);
				}
		};
	}
}