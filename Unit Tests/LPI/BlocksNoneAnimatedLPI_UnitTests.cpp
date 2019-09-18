#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/BlocksNonAnimatedLPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"0601000003212221FF000000FF000000FF"
#define INVALID_LPI_INS		""

namespace LS
{
	TEST_CLASS(BlocksNonAnimatedLPI_GetTotalNumberOfSteps)
	{
	public:
		TEST_METHOD(IsOne)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			uint16_t steps = lpi.GetTotalNumberOfSteps();

			// assert
			Assert::AreEqual<float>(1, steps);
		}
	};

	TEST_CLASS(BlocksNonAnimatedLPI_GetOpCode)
	{
	public:
		TEST_METHOD(Is6)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(10);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			uint8_t opcode = lpi.GetOpCode();

			// assert
			Assert::AreEqual<uint8_t>(6, opcode);
		}
	};

	TEST_CLASS(BlocksNonAnimatedLPI_Validate)
	{
	public:
		TEST_METHOD(ValiateReturnsTrue_LPIValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_LPIInvalid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(INVALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_OpCodeIsNot01)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0001000003212221FF000000FF000000FF");
			LPIInstruction lpiIns = LPIInstruction(0, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_LPIIsNull)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(nullptr);
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_DurationIsInvalid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0600000003212221FF000000FF000000FF");
			LPIInstruction lpiIns = LPIInstruction(6, 0, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_0Blocks)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0601000000");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_1Blocks)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("060100000164FF0000");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_11Blocks)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("060100000B0909090909090909090909FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsTrue_10Blocks)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("060100000A0A0A0A0A0A0A0A0A0A0AFF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(true, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_3Blocks2Colours)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0601000003212221FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_3Blocks1Colours)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0601000003212221FF0000");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_3Blocks0Colours)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0601000003212221");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_3BlocksSpecified2Supplied)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("06010000033232FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_3BlocksSpecified1Supplied)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("06010000033200FF00");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}

		TEST_METHOD(ValiateReturnsFalse_BlocksDoNotSum100)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0601000003323232FF0000FF0000FF0000");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			bool isValid = lpi.Validate();

			// assert
			Assert::AreEqual<bool>(false, isValid);
		}
	};

	TEST_CLASS(BlocksNonAnimatedLPI_GetNextRI)
	{
	public:
		TEST_METHOD(NextRIReturnsTrue_InsIsValid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(VALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(true, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsFalse_LPIInvalid)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(100);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer(INVALID_LPI_INS);
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			Assert::AreEqual<bool>(false, nextRiRet);
		}

		TEST_METHOD(NextRIReturnsTrue_3BlockPattern193219)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0601000003193219FF000000FF00FF0000");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FF00000200FF0004FF000002", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsTrue_2BlockPattern3232)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("06010000023232FF000000FF00");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FF00000400FF0004", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsTrue_3BlockPattern212221)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("0601000003212221FF000000FF00FF0000");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FF00000300FF0002FF000003", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsTrue_5BlockPattern1717171708)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("06010000051717171708FF000000FF00FF000000FF00FF0000");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FF00000200FF0001FF00000200FF0001FF000002", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}

		TEST_METHOD(NextRIReturnsTrue_3BlockPattern40170D)
		{
			// arrange
			LEDConfig ledConfig = LEDConfig(8);
			FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);
			StringProcessor stringProcessor = StringProcessor();
			FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
			lpiBuffer.LoadFromBuffer("060100000340170DFF000000FF00FF0000");
			LPIInstruction lpiIns = LPIInstruction(6, 1, &lpiBuffer);
			BlocksNonAnimatedLPI lpi = BlocksNonAnimatedLPI(&lpiIns, &ledConfig, &stringProcessor);

			// act
			lpi.Validate();
			bool nextRiRet = lpi.GetNextRI(&riBuffer);

			// assert
			char* pRiBuffer = riBuffer.GetBuffer();
			int riBufferCompare = strcmp("FF00000600FF0001FF000001", pRiBuffer);
			Assert::AreEqual<int>(0, riBufferCompare);
		}
	};
}