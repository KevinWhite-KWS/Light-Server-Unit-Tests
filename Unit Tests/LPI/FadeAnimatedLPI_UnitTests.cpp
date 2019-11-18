#include "CppUnitTest.h"
#include "../../../Light Server/src/LPI/FadeAnimatedLPI.h"

#include "../../Helpers/LPI_UnitTestHelper.h"
#include "../../../Light Server/src/LPE.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define VALID_LPI_INS		"04010000320000000FFFFFF"
#define INVALID_LPI_INS		""

namespace LS
{
	namespace LPIS {
		namespace Fade {
			// Effect LPI:
			// 04010000 = 04 (op-code), 01 (duration), 00 (reserved), 00 (reserved)
			// 0A0 = 0A (step size), 0 (0 = fade-in, 1 = fade-out)
			// 000000 = start colour
			// FFFFFF = end colour
			// e.g. 040100000A0000000FFFFFF

			// Validation:
			// step is between 1 and 50
			// 0 or 1 for fade-in or fade-out
			// valid start colour
			// valid end colour

			// Tests ensure that the correct total number of steps
			// are reported by the effect.
			// The total steps calculated as: steps = ROUNDUP(MAX(EndR-StartR,EndG-StartG,EndB-StartB) / Step + 1)
			TEST_CLASS(FadeAnimatedLPI_GetTotalNumberOfSteps)
			{
			public:
				TEST_METHOD(Is7WhenFadeInStep50)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000320000000FFFFFF");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(7, steps);
				}

				TEST_METHOD(Is7WhenFadeOutStep50)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000321FFFFFF000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(7, steps);
				}

				TEST_METHOD(Is6WhenFadeInStep27)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "040100001B0575B5FC9CBCD");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(6, steps);
				}

				TEST_METHOD(Is5WhenFadeOutStep33)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000211979182231B1F");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(5, steps);
				}

				TEST_METHOD(Is1WhenFadeInStep10_StartExceedsEnd)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "040100000A0FFFFFF000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint16_t steps = lpi->GetTotalNumberOfSteps();

					// assert
					Assert::AreEqual<float>(1, steps);
				}
			};

			TEST_CLASS(FadeAnimatedLPI_GetOpCode)
			{
			public:
				TEST_METHOD(Is4)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, VALID_LPI_INS);
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					uint8_t opcode = lpi->GetOpCode();

					// assert
					Assert::AreEqual<uint8_t>(4, opcode);
				}
			};

			TEST_CLASS(FadeAnimatedLPI_Validate)
			{
			public:
				TEST_METHOD(ValiateReturnsTrue_LPIValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, VALID_LPI_INS);
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIInvalid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, INVALID_LPI_INS);
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_LPIIsNull)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, nullptr);
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_StepIs0)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000001979182231B1F");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_StepIs51)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000331979182231B1F");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsTrue_StepIs50)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000321979182231B1F");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsTrue_StepIs1)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000011979182231B1F");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsTrue_FadeIs0)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000010979182231B1F");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsTrue_FadeIs1)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000011979182231B1F");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(true, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_FadeIs2)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000012979182231B1F");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_StartColourMissing)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000010231B1F");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(ValiateReturnsFalse_ColoursMissing)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000010");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();

					// act
					bool isValid = lpi->Reset(lpiInstantiator.lpiInstruction);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}
			};

			TEST_CLASS(FadeAnimatedLPI_GetNextRI)
			{
			public:
				TEST_METHOD(NextRIReturnsTrue_InsIsValid)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, VALID_LPI_INS);
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
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
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, INVALID_LPI_INS);
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(false, isValid);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_BlackToWhite_Step1_Black)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000320000000FFFFFF");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					bool isValid = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("00000008", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_BlackToWhite_Step4_969696)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000320000000FFFFFF");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 3; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("96969608", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_BlackToWhite_Step6_FAFAFA)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000320000000FFFFFF");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 5; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FAFAFA08", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_BlackToWhite_Step7_FFFFFF)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000320000000FFFFFF");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 6; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FFFFFF08", &riBuffer));
					lpiInstantiator.CleanUp(lpi);;
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_BlackToWhite_Step8_FalseReturned)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000320000000FFFFFF");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 7; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					bool hasNextRi = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(false, hasNextRi);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_WhiteToBlack_Step1_White)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000321FFFFFF000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FFFFFF08", &riBuffer));
					lpiInstantiator.CleanUp(lpi);;
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_WhiteToBlack_Step2_CDCDCD)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000321FFFFFF000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 1; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("CDCDCD08", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_WhiteToBlack_Step4_696969)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000321FFFFFF000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 3; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("69696908", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_WhiteToBlack_Step7_Black)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000321FFFFFF000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 6; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("00000008", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_WhiteToBlack_Step8_FalseReturned)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000321FFFFFF000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 7; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					bool hasNextRi = lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(false, hasNextRi);
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_575B5FToC9CBCD_Step1_575B5F)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "040100001B0575B5FC9CBCD");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("575B5F08", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_575B5FToC9CBCD_Step4_A8ACB0)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "040100001B0575B5FC9CBCD");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 3; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("A8ACB008", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_575B5FToC9CBCD_Step6_C9CBCD)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "040100001B0575B5FC9CBCD");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 5; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("C9CBCD08", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_97918ETo231200_Step1_97918E)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "0401000021197918E231200");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("97918E08", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_97918ETo231200_Step3_554F4C)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "0401000021197918E231200");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 2; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("554F4C08", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_97918ETo231200_Step6_554F4C)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "0401000021197918E231200");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 5; i++) lpi->GetNextRI(&riBuffer);
					riBuffer.ClearBuffer();
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("23120008", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeIn_WhiteToBlack_Step1_Black)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000210FFFFFF000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("00000008", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_FF0000ToBlack_Step1_FF0000)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000321FF0000000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					lpi->GetNextRI(&riBuffer);

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("FF000008", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_FF0000ToBlack_Step2_CD0000)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000321FF0000000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 2; i++) {
						riBuffer.ClearBuffer();
						lpi->GetNextRI(&riBuffer);
					};

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("CD000008", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}

				TEST_METHOD(NextRIReturnsExpectedRI_FadeOut_FF0000ToBlack_Step3_9B0000)
				{
					// arrange
					LPI_UnitTestHelper lpiInstantiator = LPI_UnitTestHelper(LPI_Fade, "04010000321FF0000000000");
					FadeAnimatedLPI* lpi = (FadeAnimatedLPI*)lpiInstantiator.InstantiateLPI();
					FixedSizeCharBuffer riBuffer = FixedSizeCharBuffer(1000);

					// act
					for (int i = 0; i < 3; i++) {
						riBuffer.ClearBuffer();
						lpi->GetNextRI(&riBuffer);
					};

					// assert
					Assert::AreEqual<bool>(true, lpiInstantiator.VerifyRIBuffer("9B000008", &riBuffer));
					lpiInstantiator.CleanUp(lpi);
				}
			};
		}
	}
}