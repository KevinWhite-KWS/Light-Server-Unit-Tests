#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/StochasticNonAnimatedLPI.h"

#include "../../Helpers/LPI_UnitTestHelper.h"
#include "../../../Light Server/src/LPE.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"0501000002FF000000FF00"
#define INVALID_LPI_INS		""

namespace LS
{
	namespace LPIS {
		namespace Stochastic {
			TEST_CLASS(StochasticNonAnimatedLPI_GetTotalNumberOfSteps)
			{
			public:
				TEST_METHOD(IsOne)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, VALID_LPI_INS);
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(1, steps);
				}
			};

			TEST_CLASS(StochasticNonAnimatedLPI_GetOpCode)
			{
			public:
				TEST_METHOD(Is5)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, VALID_LPI_INS);
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint8_t opcode = lpi->GetOpCode();

					// assert
					Assert::AreEqual<uint8_t>(5, opcode);
				}
			};

			TEST_CLASS(StochasticNonAnimatedLPI_Validate)
			{
			public:
				TEST_METHOD(ValiateReturnsTrue_LPIValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, VALID_LPI_INS);
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, INVALID_LPI_INS);
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIIsNull)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, nullptr);
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_DurationIsInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, VALID_LPI_INS, 0);
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_00Elements)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000000");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_01Elements)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000001FF0000");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_33Elements)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000033FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsTrue_32Elements)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000032FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_TwoElementsMissingColour)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000002FF0000");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_ThreeElementsMissingColour)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000003FF000000FF00");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_ThreeElementsMissingTwoColours)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000003FF0000");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_ThreeElementsMissingThreeColours)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000003");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}
			};

			TEST_CLASS(StochasticNonAnimatedLPI_GetNextRI)
			{
			public:
				TEST_METHOD(NextRIReturnsTrue_InsIsValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, VALID_LPI_INS);
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
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
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, INVALID_LPI_INS);
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsTrue_LEDsAreRedAndGreen)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000002FF000000FF00");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool valid = lpi->GetNextRI(&riBuffer);

					// assert
					char* pRiBuffer = riBuffer.GetBuffer();
					int countValidLEDs = 0;
					bool isValid = false;
					while (*pRiBuffer && countValidLEDs <= 8) {
						Colour colour = lpiInstantiator.stringProcessor->ExtractColourFromHexEncoded(pRiBuffer, isValid);
						pRiBuffer += 6;
						int leds = lpiInstantiator.stringProcessor->ExtractNumberFromHexEncoded(pRiBuffer, 1, 255, isValid);
						pRiBuffer += 2;
						if ((colour.red == 255 && colour.green == 0 && colour.blue == 0) ||
							(colour.red == 0 && colour.green == 255 && colour.blue == 0)) {
							countValidLEDs += leds;
						}
					}

					Assert::AreEqual<int>(8, countValidLEDs);
				}

				TEST_METHOD(NextRIReturnsTrue_LEDsAreRedAndGreenAndBlue)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000003FF000000FF000000FF");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool valid = lpi->GetNextRI(&riBuffer);

					// assert
					char* pRiBuffer = riBuffer.GetBuffer();
					int countValidLEDs = 0;
					bool isValid = false;
					while (*pRiBuffer && countValidLEDs <= 8) {
						Colour colour = lpiInstantiator.stringProcessor->ExtractColourFromHexEncoded(pRiBuffer, isValid);
						pRiBuffer += 6;
						int leds = lpiInstantiator.stringProcessor->ExtractNumberFromHexEncoded(pRiBuffer, 1, 255, isValid);
						pRiBuffer += 2;
						if ((colour.red == 255 && colour.green == 0 && colour.blue == 0) ||
							(colour.red == 0 && colour.green == 255 && colour.blue == 0) ||
							(colour.red == 0 && colour.green == 0 && colour.blue == 255)) {
							countValidLEDs += leds;
						}
					}

					Assert::AreEqual<int>(8, countValidLEDs);
				}

				TEST_METHOD(NextRIReturnsTrue_LEDsAreAABBCCAnd010203)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Stochastic, "0501000002AABBCC010203");
					StochasticNonAnimatedLPI* lpi = (StochasticNonAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool valid = lpi->GetNextRI(&riBuffer);

					// assert
					char* pRiBuffer = riBuffer.GetBuffer();
					int countValidLEDs = 0;
					bool isValid = false;
					while (*pRiBuffer && countValidLEDs <= 8) {
						Colour colour = lpiInstantiator.stringProcessor->ExtractColourFromHexEncoded(pRiBuffer, isValid);
						pRiBuffer += 6;
						int leds = lpiInstantiator.stringProcessor->ExtractNumberFromHexEncoded(pRiBuffer, 1, 255, isValid);
						pRiBuffer += 2;
						if ((colour.red == 170 && colour.green == 187 && colour.blue == 204) ||
							(colour.red == 1 && colour.green == 2 && colour.blue == 3)) {
							countValidLEDs += leds;
						}
					}

					Assert::AreEqual<int>(8, countValidLEDs);
				}

			};
		}
	}
}