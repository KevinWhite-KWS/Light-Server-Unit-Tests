#pragma once

#include "../../Light Server/src/LPE.h"
#include "../../Light Server/src/ValueDomainTypes.h"

namespace LS {
	class LPE_UnitTestHelper {
		protected:
			uint16_t noLeds = 0;


		public:
			LPE* lpe = nullptr;
			LEDConfig* ledConfig = nullptr;
			StringProcessor* stringProcessor = nullptr;

			LPE_UnitTestHelper(uint16_t noLeds = 8) {
				this->noLeds = noLeds;
			}

			LPE* InstantiateLPE() {
				this->ledConfig = new LEDConfig(this->noLeds);
				this->stringProcessor = new StringProcessor();
				this->lpe = new LPE(ledConfig, stringProcessor);

				return this->lpe;
			}

			void CleanUp() {
				if (ledConfig != nullptr) free(ledConfig);
				if (stringProcessor != nullptr) free(stringProcessor);
				if (lpe != nullptr) free(lpe);
			}
	};
}
