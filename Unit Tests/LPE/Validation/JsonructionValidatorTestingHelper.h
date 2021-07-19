#include "../../../../Light-Server/src/ArduinoJson-v6.17.2.h"
#include "../../../../Light-Server/src/FixedSizeCharBuffer.h"
#include "../../../../Light-Server/src/StringProcessor.h"
#include "../../../../Light-Server/src/LPE/LpiExecutors/LpiExecutorFactory.h"

namespace LS {
	namespace LPE {
		namespace Validation {

			/*!
				@brief		Helper class to instantiate the objects in order
							to perform tests against the validation classes.
				@author		Kevin White
				@date		17 Dec 2020
			*/
			class InstructionValidatorTestingHelper {
			private:


				DynamicJsonDocument jsonDoc = DynamicJsonDocument(5000);
				FixedSizeCharBuffer lpi = FixedSizeCharBuffer(1000);
				JsonVariant elementToVerify;

				// JsonVariant* elementToValdiate;
			public:


				LEDConfig ledConfig = LEDConfig();
				StringProcessor stringProcessor;
				// LPIFactory lpiFactory = LPIFactory(&ledConfig, &stringProcessor);
				LpiExecutorFactory lpiFactory;

				InstructionValidatorTestingHelper() {
					ledConfig.numberOfLEDs = 8;
				}


				JsonVariant* GetJsonElementToValidate(const char* insBuffer) {
					lpi.LoadFromBuffer(insBuffer);
					DeserializationError error = deserializeJson(jsonDoc, lpi.GetBuffer());

					elementToVerify = jsonDoc["instructions"].getElement(0);
					return &elementToVerify;
				}
			};
		}
	}
}
