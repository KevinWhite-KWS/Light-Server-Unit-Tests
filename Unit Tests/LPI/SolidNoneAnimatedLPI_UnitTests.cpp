#include "CppUnitTest.h"
#include "../../../Light-Server/src/LPI/SolidNonAnimatedLPI.h"

#include "../../Helpers/LPI_UnitTestHelper.h"
#include "../../../Light-Server/src/LPE.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"01010000FFFFFF"
#define INVALID_LPI_INS		""
#define VALID_NEXT_RI		"00000001R"

namespace LS
{
	namespace LPIS {
		namespace Solid {
			TEST_CLASS(SolidNonAnimatedLPI_GetTotalNumberOfSteps)
			{
			public:
				TEST_METHOD(IsOne)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, VALID_LPI_INS);
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(1, steps);
				}
			};

			TEST_CLASS(SolidNonAnimatedLPI_GetOpCode)
			{
			public:
				TEST_METHOD(Is1)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, VALID_LPI_INS);
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t opcode = lpi->GetOpCode();

					// assert
					Assert::AreEqual<float>(1, opcode);
				}
			};

			TEST_CLASS(SolidNonAnimatedLPI_Validate)
			{
			public:
				TEST_METHOD(ValiateReturnsTrue_LPIValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, VALID_LPI_INS);
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, INVALID_LPI_INS);
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIIsNull)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, nullptr);
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(nullptr);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_DurationIsInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, "01000000FFFFFF");
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(nullptr);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_MissingColour)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, "01010000");
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(nullptr);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_InvalidColour)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, "01010000FFFFFH");
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(nullptr);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}
			};

			TEST_CLASS(SolidNonAnimatedLPI_GetNextRI)
			{
			public:
				TEST_METHOD(NextRIReturnsTrue_InsIsValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, VALID_LPI_INS);
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
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
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, INVALID_LPI_INS);
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_ColourIsWhite)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, "01010000FFFFFF");
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FFFFFF01R", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_ColourIsBlack)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, "01010000000000");
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("00000001R", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_ColourIsFixed)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Solid, "01010000FA052A");
					SolidNonAnimatedLPI* lpi = (SolidNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FA052A01R", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}
			};
		}
	}
}