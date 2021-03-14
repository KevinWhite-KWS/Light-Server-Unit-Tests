#include "CppUnitTest.h"

#include "..\..\..\..\Light-Server\src\LPE\EffectHelpers\GradientEffect.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace Effects {
			namespace GradientEffect {
				class GradientEffectTester : public GradientEffect {
				public:
					uint8_t* getAbsDistances() {
						return this->absDistances;
					}

					int* getStepDirections() {
						return this->stepDirections;
					}

					double* getStepValues() {
						return this->stepValues;
					}
				};

				TEST_CLASS(Reset)
				{
				public:
					TEST_METHOD(WhenResetToRedBlue8Steps_CorrectAbsDirectionsStepValsSet)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(255, 0, 0);
						Colour backgroundColour = Colour(0, 0, 255);
						uint8_t steps = 8;

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						uint8_t* actualAbsDistances = gradientEffect.getAbsDistances();
						int* actualStepDirections = gradientEffect.getStepDirections();
						double* actualStepValues = gradientEffect.getStepValues();

						// assert
						uint8_t expectedAbsDistances[3] = { 255, 0, 255 };
						int expectedStepDirections[3] = { -1, 1, 1 };
						int expectedStepVals[3] = { -28, 0, 28 };
						for (int i = 0; i < 3; i++) {
							Assert::AreEqual<uint8_t>(expectedAbsDistances[i], actualAbsDistances[i]);
							Assert::AreEqual<int>(expectedStepDirections[i], actualStepDirections[i]);
							Assert::AreEqual<int>(expectedStepVals[i], (int)actualStepValues[i]);
						}
					}

					TEST_METHOD(WhenResetToRedBlue4Steps_CorrectAbsDirectionsStepValsSet)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(255, 0, 0);
						Colour backgroundColour = Colour(0, 0, 255);
						uint8_t steps = 4;

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						uint8_t* actualAbsDistances = gradientEffect.getAbsDistances();
						int* actualStepDirections = gradientEffect.getStepDirections();
						double* actualStepValues = gradientEffect.getStepValues();

						// assert
						uint8_t expectedAbsDistances[3] = { 255, 0, 255 };
						int expectedStepDirections[3] = { -1, 1, 1 };
						int expectedStepVals[3] = { -51, 0, 51 };
						for (int i = 0; i < 3; i++) {
							Assert::AreEqual<uint8_t>(expectedAbsDistances[i], actualAbsDistances[i]);
							Assert::AreEqual<int>(expectedStepDirections[i], actualStepDirections[i]);
							Assert::AreEqual<int>(expectedStepVals[i], (int)actualStepValues[i]);
						}
					}

					TEST_METHOD(WhenResetToRedBlue16Steps_CorrectAbsDirectionsStepValsSet)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(255, 0, 0);
						Colour backgroundColour = Colour(0, 0, 255);
						uint8_t steps = 16;

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						uint8_t* actualAbsDistances = gradientEffect.getAbsDistances();
						int* actualStepDirections = gradientEffect.getStepDirections();
						double* actualStepValues = gradientEffect.getStepValues();

						// assert
						uint8_t expectedAbsDistances[3] = { 255, 0, 255 };
						int expectedStepDirections[3] = { -1, 1, 1 };
						int expectedStepVals[3] = { -15, 0, 15 };
						for (int i = 0; i < 3; i++) {
							Assert::AreEqual<uint8_t>(expectedAbsDistances[i], actualAbsDistances[i]);
							Assert::AreEqual<int>(expectedStepDirections[i], actualStepDirections[i]);
							Assert::AreEqual<int>(expectedStepVals[i], (int)actualStepValues[i]);
						}
					}

					TEST_METHOD(WhenResetToComplexColour1And10Steps_CorrectAbsDirectionsStepValsSet)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(75, 210, 65);
						Colour backgroundColour = Colour(35, 225, 125);
						uint8_t steps = 10;

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						uint8_t* actualAbsDistances = gradientEffect.getAbsDistances();
						int* actualStepDirections = gradientEffect.getStepDirections();
						double* actualStepValues = gradientEffect.getStepValues();

						// assert
						uint8_t expectedAbsDistances[3] = { 40, 15, 60 };
						int expectedStepDirections[3] = { -1, 1, 1 };
						int expectedStepVals[3] = { -3, 1, 5 };
						for (int i = 0; i < 3; i++) {
							Assert::AreEqual<uint8_t>(expectedAbsDistances[i], actualAbsDistances[i]);
							Assert::AreEqual<int>(expectedStepDirections[i], actualStepDirections[i]);
							Assert::AreEqual<int>(expectedStepVals[i], (int)actualStepValues[i]);
						}
					}

					TEST_METHOD(WhenResetToComplexColour2And17Steps_CorrectAbsDirectionsStepValsSet)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(35, 45, 55);
						Colour backgroundColour = Colour(225, 235, 245);
						uint8_t steps = 17;

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						uint8_t* actualAbsDistances = gradientEffect.getAbsDistances();
						int* actualStepDirections = gradientEffect.getStepDirections();
						double* actualStepValues = gradientEffect.getStepValues();

						// assert
						uint8_t expectedAbsDistances[3] = { 190, 190, 190 };
						int expectedStepDirections[3] = { 1, 1, 1 };
						int expectedStepVals[3] = { 10, 10, 10 };
						for (int i = 0; i < 3; i++) {
							Assert::AreEqual<uint8_t>(expectedAbsDistances[i], actualAbsDistances[i]);
							Assert::AreEqual<int>(expectedStepDirections[i], actualStepDirections[i]);
							Assert::AreEqual<int>(expectedStepVals[i], (int)actualStepValues[i]);
						}
					}
				};

				TEST_CLASS(CalculateStepColour)
				{
				public:
					TEST_METHOD(WhenRedBlue8StepsStep0Requested_BlackReturned)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(255, 0, 0);
						Colour backgroundColour = Colour(0, 0, 255);
						const uint8_t steps = 1;
						Colour actualColours[steps];

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						for (int i = 0; i < steps; i++) {
							gradientEffect.CalculatetepColour(i, actualColours[i]);
						}

						// assert
						Colour expectedColours[steps] = {
							Colour(0,0,0),
						};
						for (int i = 0; i < steps; i++) {
							bool coloursAreEqual = expectedColours[i] == actualColours[i];
							Assert::IsTrue(coloursAreEqual);
						}
					}

					TEST_METHOD(WhenRedBlue8StepsStep9Requested_BlackReturned)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(255, 0, 0);
						Colour backgroundColour = Colour(0, 0, 255);
						const uint8_t steps = 8;
						Colour actualColours[steps];

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						Colour gradientColour;
						gradientEffect.CalculatetepColour(9, gradientColour);

						// assert
						Assert::IsTrue(gradientColour == Colour(0, 0, 0));
					}


					TEST_METHOD(WhenRedBlue8Steps_CorrectColoursSet)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(255, 0, 0);
						Colour backgroundColour = Colour(0, 0, 255);
						const uint8_t steps = 8;
						Colour actualColours[steps];

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						for (int i = 0; i < steps; i++) {
							gradientEffect.CalculatetepColour(i + 1, actualColours[i]);
						}
						
						// assert
						Colour expectedColours[steps] = {
							Colour(227,0,28),
							Colour(198,0,57),
							Colour(170,0,85),
							Colour(142,0,113),
							Colour(113,0,142),
							Colour(85,0,170),
							Colour(57,0,198),
							Colour(28,0,227)
						};
						for (int i = 0; i < steps; i++) {
							bool coloursAreEqual = expectedColours[i] == actualColours[i];
							Assert::IsTrue(coloursAreEqual);
						}
					}

					TEST_METHOD(WhenRedBlue16Steps_CorrectColoursSet)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(255, 0, 0);
						Colour backgroundColour = Colour(0, 0, 255);
						const uint8_t steps = 16;
						Colour actualColours[steps];

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						for (int i = 0; i < steps; i++) {
							gradientEffect.CalculatetepColour(i + 1, actualColours[i]);
						}

						// assert
						Colour expectedColours[steps] = {
							Colour(240,0,15),
							Colour(225,0,30),
							Colour(210,0,45),
							Colour(195,0,60),
							Colour(180,0,75),
							Colour(165,0,90),
							Colour(150,0,105),
							Colour(135,0,120),
							Colour(120,0,135),
							Colour(105,0,150),
							Colour(90,0,165),
							Colour(75,0,180),
							Colour(60,0,195),
							Colour(45,0,210),
							Colour(30,0,225),
							Colour(15,0,240)
						};
						for (int i = 0; i < steps; i++) {
							bool coloursAreEqual = expectedColours[i] == actualColours[i];
							Assert::IsTrue(coloursAreEqual);
						}
					}

					TEST_METHOD(WhenRedBlue4Steps_CorrectColoursSet)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(255, 0, 0);
						Colour backgroundColour = Colour(0, 0, 255);
						const uint8_t steps = 4;
						Colour actualColours[steps];

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						for (int i = 0; i < steps; i++) {
							gradientEffect.CalculatetepColour(i + 1, actualColours[i]);
						}

						// assert
						Colour expectedColours[steps] = {
							Colour(204,0,51),
							Colour(153,0,102),
							Colour(102,0,153),
							Colour(51,0,204)
						};
						for (int i = 0; i < steps; i++) {
							bool coloursAreEqual = expectedColours[i] == actualColours[i];
							Assert::IsTrue(coloursAreEqual);
						}
					}

					TEST_METHOD(WhenComplexColours1And10Steps_CorrectColoursSet)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(75, 210, 65);
						Colour backgroundColour = Colour(35, 225, 125);
						const uint8_t steps = 10;
						Colour actualColours[steps];

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						for (int i = 0; i < steps; i++) {
							gradientEffect.CalculatetepColour(i + 1, actualColours[i]);
						}

						// assert
						Colour expectedColours[steps] = {
							Colour(71,211,70),
							Colour(68,213,76),
							Colour(64,214,81),
							Colour(60,215,87),
							Colour(57,217,92),
							Colour(53,218,98),
							Colour(50,220,103),
							Colour(46,221,109),
							Colour(42,222,114),
							Colour(39,224,120)
						};
						for (int i = 0; i < steps; i++) {
							bool coloursAreEqual = expectedColours[i] == actualColours[i];
							Assert::IsTrue(coloursAreEqual);
						}
					}

					TEST_METHOD(WhenComplexColours2And17Steps_CorrectColoursSet)
					{
						// arrange
						GradientEffectTester gradientEffect;
						Colour startColour = Colour(35, 45, 55);
						Colour backgroundColour = Colour(225, 235, 245);
						const uint8_t steps = 17;
						Colour actualColours[steps];

						// act
						gradientEffect.Reset(startColour, backgroundColour, steps);
						for (int i = 0; i < steps; i++) {
							gradientEffect.CalculatetepColour(i + 1, actualColours[i]);
						}

						// assert
						Colour expectedColours[steps] = {
							Colour(46,56,66),
							Colour(56,66,76),
							Colour(67,77,87),
							Colour(77,87,97),
							Colour(88,98,108),
							Colour(98,108,118),
							Colour(109,119,129),
							Colour(119,129,139),
							Colour(130,140,150),
							Colour(141,151,161),
							Colour(151,161,171),
							Colour(162,172,182),
							Colour(172,182,192),
							Colour(183,193,203),
							Colour(193,203,213),
							Colour(204,214,224),
							Colour(214,224,234)
						};
						for (int i = 0; i < steps; i++) {
							bool coloursAreEqual = expectedColours[i] == actualColours[i];
							Assert::IsTrue(coloursAreEqual);
						}
					}
				};
			}
		}
	}
}