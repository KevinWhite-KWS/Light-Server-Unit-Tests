#include "CppUnitTest.h"
#include "..\..\Light Server\src\LPE.h"
#include "..\mocks\Mock_LPE.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS
{
	TEST_CLASS(LPE_GetLPI) {
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
}