#include "../pch.h"
#include "CppUnitTest.h"
#include "../../Light-Server/src/Renderer.h"
#include "../../Light-Server/src/ValueDomainTypes.h"
#include "../../Light-Server/src/DomainInterfaces.h"
#include "../mocks/Mock_Adafruit_NeoPixel.h"
#include "../mocks/Mock_Renderer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS
{
	class RendererTestClasses
	{
		public:
			StringProcessor* stringProcessor = new StringProcessor();
			LEDConfig* ledConfig = nullptr;
			Mock_Adafruit_NeoPixel* pixelController = new Mock_Adafruit_NeoPixel(5);
			Mock_Renderer* renderer;

			RendererTestClasses(uint8_t noLeds = 10) {
				ledConfig = new LEDConfig(noLeds);
				IPixelController* p = pixelController;
				renderer = new Mock_Renderer(stringProcessor, ledConfig, p);
			}

			~RendererTestClasses() {
				delete stringProcessor;
				delete ledConfig;
				delete pixelController;
				delete renderer;
			}
	};

	TEST_CLASS(Renderer_SetRI) {
		public:
			/*** ONE GROUP NEGATIVE TESTS ***/
			TEST_METHOD(InvalidInstruction)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("abc");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_NullString)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI(nullptr);

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_EmptyString)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidRedColour_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("G0000001");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidGreenColour_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("00G00001");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidBlueColour_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("0000G001");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidNumber1_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("00000000");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidNumber2_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("000000G0");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_MissingOneColour_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("000001");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_MissingTwoColours_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("0001");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_MissingThreeColours_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("01");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_MissingNumber_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_MissingSingleDigit_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF1");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidRepeat_OneGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF01P");

				// assert
				Assert::IsFalse(result);
			}


			/*** TWO GROUP NEGATIVE TESTS ***/
			TEST_METHOD(InvalidInstruction_InvalidRedColour_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF01G0000001");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidGreenColour_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF0100G00001");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidBlueColour_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF010000G001");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidNumber1_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF0100000000");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidNumber2_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF01000000G0");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_MissingOneColour_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF01000001");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_MissingTwoColours_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF010001");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_MissingThreeColours_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF0101");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_MissingNumber_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF01FFFFFF");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_MissingSingleDigit_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF01FFFFFF1");

				// assert
				Assert::IsFalse(result);
			}

			TEST_METHOD(InvalidInstruction_InvalidRepeat_TwoGroup)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF01FFFFFF01P");

				// assert
				Assert::IsFalse(result);
			}



			/*** POSITIVE TESTS ***/
			TEST_METHOD(ValidInstruction_LowerColourBoundary)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("00000005");

				// assert
				Assert::IsTrue(result);
				Colour expectedColours[5] = { Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0) };
				Assert::IsTrue(testClasses.pixelController->checkSetLeds(expectedColours, 5));
			}

			TEST_METHOD(ValidInstruction_UpperColourBoundary)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF01");

				// assert
				Assert::IsTrue(result);
				Colour expectedColours[5] = { Colour(255, 255, 255), Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0) };
				Assert::IsTrue(testClasses.pixelController->checkSetLeds(expectedColours, 5));
			}

			TEST_METHOD(ValidInstruction_UpperNumberBoundary)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFFFF");

				// assert
				Assert::IsTrue(result);
				Colour expectedColours[5] = { Colour(255, 255, 255), Colour(255, 255, 255), Colour(255, 255, 255), Colour(255, 255, 255), Colour(255, 255, 255) };
				Assert::IsTrue(testClasses.pixelController->checkSetLeds(expectedColours, 5));
			}

			TEST_METHOD(ValidInstruction_RandomColour1)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("000A1005");

				// assert
				Assert::IsTrue(result);
				Colour expectedColours[5] = { Colour(00, 10, 16), Colour(00, 10, 16), Colour(00, 10, 16), Colour(00, 10, 16), Colour(00, 10, 16) };
				Assert::IsTrue(testClasses.pixelController->checkSetLeds(expectedColours, 5));
			}

			TEST_METHOD(ValidInstruction_RandomColour2)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FA3FE904");

				// assert
				Assert::IsTrue(result);
				Colour expectedColours[5] = { Colour(250, 63, 233), Colour(250, 63, 233), Colour(250, 63, 233), Colour(250, 63, 233), Colour(0, 0, 0) };
				Assert::IsTrue(testClasses.pixelController->checkSetLeds(expectedColours, 5));
			}

			TEST_METHOD(ValidInstruction_RandomColour3)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("8B6C5D01");

				// assert
				Assert::IsTrue(result);
				Colour expectedColours[5] = { Colour(139, 108, 93), Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0) };
				Assert::IsTrue(testClasses.pixelController->checkSetLeds(expectedColours, 5));
			}

			TEST_METHOD(ValidInstruction_RandomColour4)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("3E2B1A02");

				// assert
				Assert::IsTrue(result);
				Colour expectedColours[5] = { Colour(62, 43, 26), Colour(62, 43, 26), Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0) };
				Assert::IsTrue(testClasses.pixelController->checkSetLeds(expectedColours, 5));
			}

			TEST_METHOD(ValidInstruction_Repeat)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("FFFFFF01R");

				// assert
				Assert::IsTrue(result);
				Colour expectedColours[5] = { Colour(255, 255, 255), Colour(255, 255, 255), Colour(255, 255, 255), Colour(255, 255, 255), Colour(255, 255, 255) };
				Assert::IsTrue(testClasses.pixelController->checkSetLeds(expectedColours, 5));
			}

			TEST_METHOD(ValidInstruction_Repeat_TwoGroups)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Renderer* r = testClasses.renderer;

				// act
				bool result = r->SetRI("AABBCC011A2B3C01R");

				// assert
				Assert::IsTrue(result);
				Colour expectedColours[5] = { Colour(170, 187, 204), Colour(26, 43, 60), Colour(170, 187, 204), Colour(26, 43, 60), Colour(170, 187, 204) };
				Assert::IsTrue(testClasses.pixelController->checkSetLeds(expectedColours, 5));
			}
	};


	TEST_CLASS(Renderer_Render) {
		public:
			TEST_METHOD(NotRendered_InvalidRI)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Mock_Renderer* r = testClasses.renderer;
				r->SetLastRIInvalid();

				// act
				r->Render();

				// assert
				Assert::IsFalse(testClasses.pixelController->ledsHaveBeenRendered);
			}

			TEST_METHOD(Rendered_ValidRI)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(10);
				Mock_Renderer* r = testClasses.renderer;
				r->SetLastRIValid();

				// act
				r->Render();

				// assert
				Assert::IsTrue(testClasses.pixelController->ledsHaveBeenRendered);
			}
	};

	TEST_CLASS(Renderer_AreAnyLEDSOn) {
		public:
			TEST_METHOD(NoLedsOn)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Mock_Renderer* r = testClasses.renderer;

				// act
				bool ret = r->AreAnyLEDsOn();

				// assert
				Assert::IsFalse(ret);
			}

			TEST_METHOD(FirstLEDIsRed)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Mock_Renderer* r = testClasses.renderer;
				testClasses.pixelController->setPixelColor(0, 255, 0, 0);

				// act
				bool ret = r->AreAnyLEDsOn();

				// assert
				Assert::IsTrue(ret);
			}

			TEST_METHOD(LastLEDIsRed)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Mock_Renderer* r = testClasses.renderer;
				testClasses.pixelController->setPixelColor(4, 255, 0, 0);

				// act
				bool ret = r->AreAnyLEDsOn();

				// assert
				Assert::IsTrue(ret);
			}

			TEST_METHOD(ThirdLEDIsRed)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Mock_Renderer* r = testClasses.renderer;
				testClasses.pixelController->setPixelColor(2, 255, 0, 0);

				// act
				bool ret = r->AreAnyLEDsOn();

				// assert
				Assert::IsTrue(ret);
			}

			TEST_METHOD(AllLEDsAreRed)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Mock_Renderer* r = testClasses.renderer;
				testClasses.pixelController->setPixelColor(0, 255, 0, 0);

				// act
				bool ret = r->AreAnyLEDsOn();

				// assert
				Assert::IsTrue(ret);
			}

			TEST_METHOD(OneLEDIsNotQuiteBlack)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Mock_Renderer* r = testClasses.renderer;
				testClasses.pixelController->setPixelColor(4, 1, 0, 0);

				// act
				bool ret = r->AreAnyLEDsOn();

				// assert
				Assert::IsTrue(ret);
			}

			TEST_METHOD(OneLEDIsNotQuiteWhite)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Mock_Renderer* r = testClasses.renderer;
				testClasses.pixelController->setPixelColor(2, 254, 255, 255);

				// act
				bool ret = r->AreAnyLEDsOn();

				// assert
				Assert::IsTrue(ret);
			}

			TEST_METHOD(OneLEDIsARandomColour)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Mock_Renderer* r = testClasses.renderer;
				testClasses.pixelController->setPixelColor(2, 100, 213, 0);

				// act
				bool ret = r->AreAnyLEDsOn();

				// assert
				Assert::IsTrue(ret);
			}

			TEST_METHOD(ThreeLEDsAreARandomColour)
			{
				// arrange
				RendererTestClasses testClasses = RendererTestClasses(5);
				Mock_Renderer* r = testClasses.renderer;
				testClasses.pixelController->setPixelColor(2, 100, 213, 0);
				testClasses.pixelController->setPixelColor(4, 1, 2, 3);
				testClasses.pixelController->setPixelColor(5, 50, 12, 0);

				// act
				bool ret = r->AreAnyLEDsOn();

				// assert
				Assert::IsTrue(ret);
			}
	};
}
