#ifndef _MOCK_ADAFRUIT_NEOPIXEL
#define _MOCK_ADAFRUIT_NEOPIXEL_

#include <stdint.h>
#include "..\..\Light-Server\src\DomainInterfaces.h"
#include "..\..\Light-Server\src\ValueDomainTypes.h"

namespace LS {
	class Mock_Adafruit_NeoPixel : public IPixelController {
		private:
			Colour colours[5];
			uint8_t numberOfLeds;

		public:
			bool ledsHaveBeenRendered = false;

			Mock_Adafruit_NeoPixel(uint8_t numberOfLeds) {
				// colours = Colour[numberOfLeds];
				this->numberOfLeds = numberOfLeds;
			}

			virtual void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
				if (n >= numberOfLeds) return;

				colours[n] = Colour(r, g, b);
			}

			bool checkSetLeds(Colour expectedColours[], uint8_t numLedsExpected) {
				bool isCorrect = true;

				for (int i = 0; i < numLedsExpected && isCorrect; i++) {
					Colour expectedColour = expectedColours[i];
					Colour actualColour = colours[i];

					isCorrect = expectedColour.red == actualColour.red
						&& expectedColour.green == actualColour.green
						&& expectedColour.blue == actualColour.blue;
				}

				return isCorrect;
			}

			void show() {
				ledsHaveBeenRendered = true;
			}

			uint32_t getPixelColor(uint16_t n) const {
				uint32_t pixelColour = 0;

				if (n < numberOfLeds) {
					pixelColour = colours[n].red << 24;
					pixelColour = pixelColour | colours[n].green << 16;
					pixelColour = pixelColour | colours[n].blue << 8;
				}


				return pixelColour;
			}

			void fill(uint32_t c = 0, uint16_t first = 0, uint16_t count = 0) {
			}

			uint16_t numPixels(void) const {
				return 0;
			}
	};
}
#endif
