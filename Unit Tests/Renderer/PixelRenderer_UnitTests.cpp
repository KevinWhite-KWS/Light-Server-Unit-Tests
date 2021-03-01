#include "../../pch.h"
#include "CppUnitTest.h"
#include "../../../Light-Server/src/Renderer/PixelRenderer.h"
#include "../../../Light-Server/src/ValueDomainTypes.h"
#include "../../../Light-Server/src/DomainInterfaces.h"
#include "../../mocks/Mock_Adafruit_NeoPixel.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS
{
	//class RendererTestClasses
	//{
	//public:
	//	StringProcessor* stringProcessor = new StringProcessor();
	//	LEDConfig* ledConfig = nullptr;
	//	Mock_Adafruit_NeoPixel* pixelController = new Mock_Adafruit_NeoPixel(5);
	//	Mock_Renderer* renderer;

	//	RendererTestClasses(uint8_t noLeds = 10) {
	//		ledConfig = new LEDConfig(noLeds);
	//		IPixelController* p = pixelController;
	//		renderer = new Mock_Renderer(stringProcessor, ledConfig, p);
	//	}

	//	~RendererTestClasses() {
	//		delete stringProcessor;
	//		delete ledConfig;
	//		delete pixelController;
	//		delete renderer;
	//	}
	//};
	namespace Render {
		TEST_CLASS(Renderer_SetPixels) {
			public:
				TEST_METHOD(NullLpiParams_FalseReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);

					// act
					bool pixelsSet = pixelRenderer.SetPixels(nullptr);

					// assert
					Assert::IsFalse(pixelsSet);
				}

				TEST_METHOD(NumberOfRIsIsZero_FalseReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsFalse(pixelsSet);
				}

				TEST_METHOD(FivePixelsToBlack_PixelsSet)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(5);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(5);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;
					lpiOutput.SetNextRenderingInstruction(&Colour(0, 0, 0), 5);

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsTrue(pixelsSet);
					Colour expectedColours[5] = { Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0), Colour(0, 0, 0) };
					Assert::IsTrue(mockPixelController.checkSetLeds(expectedColours, 5));
				}

				TEST_METHOD(FivePixelsToWhite_PixelsSet)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(5);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(5);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;
					lpiOutput.SetNextRenderingInstruction(&Colour(255, 255, 255), 5);

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsTrue(pixelsSet);
					Colour expectedColours[5] = { 
						Colour(255, 255, 255),
						Colour(255, 255, 255),
						Colour(255, 255, 255),
						Colour(255, 255, 255),
						Colour(255, 255, 255) };
					Assert::IsTrue(mockPixelController.checkSetLeds(expectedColours, 5));
				}

				TEST_METHOD(OnePixelSetToWhite_PixelsSet)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(5);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(5);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;
					lpiOutput.SetNextRenderingInstruction(&Colour(255, 255, 255), 1);

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsTrue(pixelsSet);
					Colour expectedColours[5] = {
						Colour(255, 255, 255),
						Colour(0, 0, 0),
						Colour(0, 0, 0),
						Colour(0, 0, 0),
						Colour(0, 0, 0) };
					Assert::IsTrue(mockPixelController.checkSetLeds(expectedColours, 5));
				}

				TEST_METHOD(FivePixelsSetToRandomColour_PixelsSet)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(5);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(5);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;
					lpiOutput.SetNextRenderingInstruction(&Colour(0, 10, 16), 5);

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsTrue(pixelsSet);
					uint8_t r = 0, g = 10, b = 16;
					Colour expectedColours[5] = {
						Colour(r, g, b),
						Colour(r, g, b),
						Colour(r, g, b),
						Colour(r, g, b),
						Colour(r, g, b) };
					Assert::IsTrue(mockPixelController.checkSetLeds(expectedColours, 5));
				}

				TEST_METHOD(FivePixelsSetToRandomColour2_PixelsSet)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(5);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(5);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;
					lpiOutput.SetNextRenderingInstruction(&Colour(250, 63, 233), 4);

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsTrue(pixelsSet);
					uint8_t r = 250, g = 63, b = 233;
					Colour expectedColours[5] = {
						Colour(r, g, b),
						Colour(r, g, b),
						Colour(r, g, b),
						Colour(r, g, b),
						Colour(0, 0, 0) };
					Assert::IsTrue(mockPixelController.checkSetLeds(expectedColours, 5));
				}

				TEST_METHOD(FivePixelsSetToRandomColour3_PixelsSet)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(5);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(5);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;
					lpiOutput.SetNextRenderingInstruction(&Colour(139, 108, 93), 1);

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsTrue(pixelsSet);
					uint8_t r = 139, g = 108, b = 93;
					Colour expectedColours[5] = {
						Colour(r, g, b),
						Colour(0, 0, 0),
						Colour(0, 0, 0),
						Colour(0, 0, 0),
						Colour(0, 0, 0) };
					Assert::IsTrue(mockPixelController.checkSetLeds(expectedColours, 5));
				}

				TEST_METHOD(FivePixelsSetToRandomColour4_PixelsSet)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(5);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(5);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;
					lpiOutput.SetNextRenderingInstruction(&Colour(62, 43, 26), 1);

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsTrue(pixelsSet);
					uint8_t r = 62, g = 43, b = 26;
					Colour expectedColours[5] = {
						Colour(r, g, b),
						Colour(0, 0, 0),
						Colour(0, 0, 0),
						Colour(0, 0, 0),
						Colour(0, 0, 0) };
					Assert::IsTrue(mockPixelController.checkSetLeds(expectedColours, 5));
				}

				TEST_METHOD(RepeatWhite_PixelsSet)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(5);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(5);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;
					lpiOutput.SetNextRenderingInstruction(&Colour(255, 255, 255), 1);
					lpiOutput.SetRepeatRenderingInstructions();

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsTrue(pixelsSet);
					uint8_t r = 255, g = 255, b = 255;
					Colour expectedColours[5] = {
						Colour(r, g, b),
						Colour(r, g, b),
						Colour(r, g, b),
						Colour(r, g, b),
						Colour(r, g, b) };
					Assert::IsTrue(mockPixelController.checkSetLeds(expectedColours, 5));
				}

				TEST_METHOD(RepeatTwoGroups_PixelsSet)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(5);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(5);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;
					lpiOutput.SetNextRenderingInstruction(&Colour(170, 187, 204), 1);
					lpiOutput.SetNextRenderingInstruction(&Colour(26, 43, 60), 1);
					lpiOutput.SetRepeatRenderingInstructions();

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsTrue(pixelsSet);
					uint8_t r = 255, g = 255, b = 255;
					Colour expectedColours[5] = {
						Colour(170, 187, 204),
						Colour(26, 43, 60),
						Colour(170, 187, 204),
						Colour(26, 43, 60),
						Colour(170, 187, 204) };
					Assert::IsTrue(mockPixelController.checkSetLeds(expectedColours, 5));
				}

				TEST_METHOD(TooManyRIs_FirstFewPixelsSet)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(5);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(5);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);
					LpiExecutorOutput lpiOutput;
					lpiOutput.SetNextRenderingInstruction(&Colour(0, 0, 0), 1);
					lpiOutput.SetNextRenderingInstruction(&Colour(1, 1, 1), 1);
					lpiOutput.SetNextRenderingInstruction(&Colour(2, 2, 2), 1);
					lpiOutput.SetNextRenderingInstruction(&Colour(3, 3, 3), 1);
					lpiOutput.SetNextRenderingInstruction(&Colour(4, 4, 4), 1);
					lpiOutput.SetNextRenderingInstruction(&Colour(5, 5, 5), 1);

					// act
					bool pixelsSet = pixelRenderer.SetPixels(&lpiOutput);

					// assert
					Assert::IsTrue(pixelsSet);
					uint8_t r = 255, g = 255, b = 255;
					Colour expectedColours[5] = {
						Colour(0, 0, 0),
						Colour(1, 1, 1),
						Colour(2, 2, 2),
						Colour(3, 3, 3),
						Colour(4, 4, 4) };
					Assert::IsTrue(mockPixelController.checkSetLeds(expectedColours, 5));
				}
		};


		TEST_CLASS(Renderer_AreAnyLEDSOn) {
			public:
				TEST_METHOD(NoLedsOn_FalseReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);

					// act
					bool anyPixelsOn = pixelRenderer.AreAnyPixelsOn();

					// assert
					Assert::IsFalse(anyPixelsOn);
				}

				TEST_METHOD(FirstLedIsRed_TrueReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					mockPixelController.setPixelColor(0, 255, 0, 0);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);

					// act
					bool anyPixelsOn = pixelRenderer.AreAnyPixelsOn();

					// assert
					Assert::IsTrue(anyPixelsOn);
				}

				TEST_METHOD(LastLedIsRed_TrueReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					mockPixelController.setPixelColor(7, 255, 0, 0);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);

					// act
					bool anyPixelsOn = pixelRenderer.AreAnyPixelsOn();

					// assert
					Assert::IsTrue(anyPixelsOn);
				}

				TEST_METHOD(ThirdLedIsRed_TrueReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					mockPixelController.setPixelColor(2, 255, 0, 0);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);

					// act
					bool anyPixelsOn = pixelRenderer.AreAnyPixelsOn();

					// assert
					Assert::IsTrue(anyPixelsOn);
				}

				TEST_METHOD(AllLedsAreRed_TrueReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					for (int i = 0; i < 8; i++) { mockPixelController.setPixelColor(i, 255, 0, 0); }
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);

					// act
					bool anyPixelsOn = pixelRenderer.AreAnyPixelsOn();

					// assert
					Assert::IsTrue(anyPixelsOn);
				}

				TEST_METHOD(OneLedIsNotQuiteBlack_TrueReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					mockPixelController.setPixelColor(4, 1, 0, 0);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);

					// act
					bool anyPixelsOn = pixelRenderer.AreAnyPixelsOn();

					// assert
					Assert::IsTrue(anyPixelsOn);
				}

				TEST_METHOD(OneLedIsNotQuiteWhite_TrueReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					mockPixelController.setPixelColor(2, 254, 255, 255);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);

					// act
					bool anyPixelsOn = pixelRenderer.AreAnyPixelsOn();

					// assert
					Assert::IsTrue(anyPixelsOn);
				}

				TEST_METHOD(OneLedIsARandomColour_TrueReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					mockPixelController.setPixelColor(2, 100, 213, 0);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);

					// act
					bool anyPixelsOn = pixelRenderer.AreAnyPixelsOn();

					// assert
					Assert::IsTrue(anyPixelsOn);
				}

				TEST_METHOD(ThreeLedsAreARandomColour_TrueReturned)
				{
					// arrange
					LEDConfig ledConfig = LEDConfig(8);
					Mock_Adafruit_NeoPixel mockPixelController = Mock_Adafruit_NeoPixel(8);
					mockPixelController.setPixelColor(2, 100, 213, 0);
					mockPixelController.setPixelColor(4, 1, 2, 3);
					mockPixelController.setPixelColor(5, 50, 12, 0);
					IPixelController* pixelController = &mockPixelController;
					PixelRenderer pixelRenderer = PixelRenderer(pixelController, &ledConfig);

					// act
					bool anyPixelsOn = pixelRenderer.AreAnyPixelsOn();

					// assert
					Assert::IsTrue(anyPixelsOn);
				}
		};
	}
}