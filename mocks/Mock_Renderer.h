#ifndef _MOCK_RENDERER_h_
#define _MOCK_RENDERER_h_

#include <stdint.h>
#include "..\..\Light Server\src\renderer.h"

namespace LS {
	class Mock_Renderer : public Renderer {
		public:
			Mock_Renderer(StringProcessor* stringProcessor, const LEDConfig* ledConfig, IPixelController* pixelController) 
				: Renderer(stringProcessor, ledConfig, pixelController) {
			}

			// only used for testing - i.e. to set the state of the last RI to be a valid RI
			void SetLastRIValid() {
				this->lastSetRiValid = true;
			}

			// only used for testing - i.e. to set the state of the last RI to be an invalid RI
			void SetLastRIInvalid() {
				this->lastSetRiValid = false;
			}
	};
}
#endif
