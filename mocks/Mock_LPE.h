#ifndef _MOCK_RENDERER_h_
#define _MOCK_RENDERER_h_

#include <stdint.h>
#include "..\..\Light Server\src\lpe.h"
#include "..\..\Light Server\src\LPI\LPI.h"

namespace LS {
	class Mock_LPE : public LPE {
		public:
			Mock_LPE(const LEDConfig* ledConfig, StringProcessor* stringProcessor)
				: LPE(ledConfig, stringProcessor) {
			}

			// only used for testing - i.e. expose protected member to ensure critical functioning is correct
			LPI* GetLPI(FixedSizeCharBuffer* instructionBuffer) {
				return LPE::GetLPI(instructionBuffer);
			}
	};
}
#endif
