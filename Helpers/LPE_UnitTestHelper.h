#pragma once

#include "../../Light-Server/src/LPE.h"
#include "../../Light-Server/src/ValueDomainTypes.h"

namespace LS {
	class LPE_UnitTestHelper {
		protected:
			uint16_t noLeds = 0;


		public:
			LPE* lpe = nullptr;
			LEDConfig* ledConfig = nullptr;
			StringProcessor* stringProcessor = nullptr;
			FixedSizeCharBuffer* riBuffer = nullptr;
			FixedSizeCharBuffer* lpBuffer = nullptr;

			LPE_UnitTestHelper(uint16_t noLeds = 8) {
				this->noLeds = noLeds;
			}

			LPE* InstantiateLPE() {
				this->ledConfig = new LEDConfig(this->noLeds);
				this->stringProcessor = new StringProcessor();
				this->lpe = new LPE(ledConfig, stringProcessor);
				this->riBuffer = new FixedSizeCharBuffer(1000);

				return this->lpe;
			}

			LPE* InstantiateLPEWithProgram(const char* lp) {
				LPE* lpe = InstantiateLPE();
				this->lpBuffer = new FixedSizeCharBuffer(1000);
				this->lpBuffer->LoadFromBuffer(lp);
				LPValidateResult result = LPValidateResult();
				lpe->ValidateLP(this->lpBuffer, &result);

				return this->lpe;
			}

			void CleanUp() {
				if (ledConfig != nullptr) free(ledConfig);
				if (stringProcessor != nullptr) free(stringProcessor);
				if (lpe != nullptr) free(lpe);
				if (riBuffer != nullptr) free(riBuffer);
				if (lpBuffer != nullptr) free(lpBuffer);
			}
	};
}
