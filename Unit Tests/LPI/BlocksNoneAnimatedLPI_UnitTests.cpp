#include "CppUnitTest.h"
#include "../../../Light-Server/src/LPI/BlocksNonAnimatedLPI.h"

#include "../../Helpers/LPI_UnitTestHelper.h"
#include "../../../Light-Server/src/LPE.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"0601000003212221FF000000FF000000FF"
#define INVALID_LPI_INS		""

namespace LS {
	namespace LPIS {
		namespace Blocks {
			TEST_CLASS(BlocksNonAnimatedLPI_GetTotalNumberOfSteps)
			{
			public:
				TEST_METHOD(IsOne)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, VALID_LPI_INS);
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

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
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, VALID_LPI_INS);
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint8_t opcode = lpi->GetOpCode();

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
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, VALID_LPI_INS);
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, INVALID_LPI_INS);
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIIsNull)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, nullptr);
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_DurationIsInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, nullptr, 0);
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_0Blocks)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "0601000000");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_1Blocks)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "060100000164FF0000");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_11Blocks)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "060100000B0909090909090909090909FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsTrue_10Blocks)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "060100000A0A0A0A0A0A0A0A0A0A0AFF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_3Blocks2Colours)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "0601000003212221FF000000FF00");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_3Blocks1Colours)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "0601000003212221FF0000");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_3Blocks0Colours)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "0601000003212221");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_3BlocksSpecified2Supplied)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "06010000033232FF000000FF00");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_3BlocksSpecified1Supplied)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "06010000033200FF00");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_BlocksDoNotSum100)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "0601000003323232FF0000FF0000FF0000");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}
			};

			TEST_CLASS(BlocksNonAnimatedLPI_GetNextRI)
			{
			public:
				TEST_METHOD(NextRIReturnsTrue_InsIsValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, VALID_LPI_INS);
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsFalse_LPIInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, INVALID_LPI_INS);
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_3BlockPattern193219)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "0601000003193219FF000000FF00FF0000");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FF00000200FF0004FF000002", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_2BlockPattern3232)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "06010000023232FF000000FF00");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FF00000400FF0004", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_3BlockPattern212221)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "0601000003212221FF000000FF00FF0000");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FF00000300FF0002FF000003", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_5BlockPattern1717171708)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "06010000051717171708FF000000FF00FF000000FF00FF0000");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FF00000200FF0001FF00000200FF0001FF000002", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_3BlockPattern40170D)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Blocks, "060100000340170DFF000000FF00FF0000");
					BlocksNonAnimatedLPI* lpi = (BlocksNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FF00000600FF0001FF000001", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}
			};
		}
	}
}