#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/ClearNonAnimatedLPI.h"

#include "../../Helpers/LPI_UnitTestHelper.h"
#include "../../../Light Server/src/LPE.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"00010000"
#define INVALID_LPI_INS		""
#define VALID_NEXT_RI		"00000001R"

namespace LS
{
	namespace LPIS {
		namespace Clear {
			TEST_CLASS(ClearNonAnimatedLPI_GetTotalNumberOfSteps)
			{
			public:
				TEST_METHOD(IsOne)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Clear, VALID_LPI_INS);
					ClearNonAnimatedLPI* lpi = (ClearNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(1, steps);
				}
			};

			TEST_CLASS(ClearNonAnimatedLPI_GetOpCode)
			{
			public:
				TEST_METHOD(Is0)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Clear, VALID_LPI_INS);
					ClearNonAnimatedLPI* lpi = (ClearNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t opcode = lpi->GetOpCode();

					// assert
					Assert::AreEqual<float>(0, opcode);
				}
			};

			TEST_CLASS(ClearNonAnimatedLPI_Validate)
			{
			public:
				TEST_METHOD(ValiateReturnsTrue_LPIValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Clear, VALID_LPI_INS);
					ClearNonAnimatedLPI* lpi = (ClearNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIIsNull)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Clear, nullptr);
					ClearNonAnimatedLPI* lpi = (ClearNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(nullptr);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}
			};

			TEST_CLASS(ClearNonAnimatedLPI_GetNextRI)
			{
			public:
				TEST_METHOD(NextRIReturnsTrue_LPIValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Clear, VALID_LPI_INS);
					ClearNonAnimatedLPI* lpi = (ClearNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_RIInstructionAsExpected)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Clear, VALID_LPI_INS);
					ClearNonAnimatedLPI* lpi = (ClearNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("00000001R", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}
			};
		}
	}
}