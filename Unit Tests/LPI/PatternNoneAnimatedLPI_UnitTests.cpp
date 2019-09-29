#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/PatternNonAnimatedLPI.h"

#include "../../Helpers/LPI_UnitTestHelper.h"
#include "../../../Light Server/src/LPE.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"0201000002010200FF00FF0000"
#define INVALID_LPI_INS		""
#define VALID_NEXT_RI		"00000001R"

namespace LS
{
	namespace LPIS {
		namespace Pattern {
			TEST_CLASS(PatternNonAnimatedLPI_GetTotalNumberOfSteps)
			{
			public:
				TEST_METHOD(IsOne)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, VALID_LPI_INS);
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(1, steps);
				}
			};

			TEST_CLASS(PatternNonAnimatedLPI_GetOpCode)
			{
			public:
				TEST_METHOD(Is2)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, VALID_LPI_INS);
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t opcode = lpi->GetOpCode();

					// assert
					Assert::AreEqual<float>(2, opcode);
				}
			};

			TEST_CLASS(PatternNonAnimatedLPI_Validate)
			{
			public:
				TEST_METHOD(ValiateReturnsTrue_LPIValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, VALID_LPI_INS);
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, INVALID_LPI_INS);
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIIsNull)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, nullptr);
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(nullptr);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_DurationIsInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, nullptr, 0);
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_0Blocks)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, "0201000000010200FF00FF0000");
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_2BlocksMissing1)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, "02010000020200FF00FF0000");
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_2BlocksMissing1Colour)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, "0201000002010200FF00");
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_BlocksExceedsLEDS)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, "0201000002040500FF00FF0000");
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

			};

			TEST_CLASS(PatternNonAnimatedLPI_GetNextRI)
			{
			public:
				TEST_METHOD(NextRIReturnsTrue_InsIsValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, VALID_LPI_INS);
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
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
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, INVALID_LPI_INS);
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_ColourIsHalfGreenAndHalfRed)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, "0201000002040400FF00FF0000");
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("00FF0004FF000004R", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_AlternateRedGreen)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, "02010000020101FF000000FF00");
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FF00000100FF0001R", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_ThreeGroups)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Pattern, "0201000003030201FF000000FF000000FF");
					PatternNonAnimatedLPI* lpi = (PatternNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FF00000300FF00020000FF01R", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}
			};
		}
	}
}