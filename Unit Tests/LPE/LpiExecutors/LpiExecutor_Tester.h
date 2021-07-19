#include "..\..\..\..\Light-Server\src\ValueDomainTypes.h"
#include "..\..\..\..\Light-Server\src\StringProcessor.h"
#include "..\..\..\..\Light-Server\src\LPE\LpiExecutors\LpiExecutorParams.h"
#include "..\..\..\..\Light-Server\src\LPE\LpiExecutors\LpiExecutor.h"

namespace LS {
	namespace LPE {
		namespace LpiExecutors {
			class LpiExecutor_Tester {
			private:
				LEDConfig ledConfig;
				StringProcessor stringProcessor;
				FixedSizeCharBuffer lpiBuffer = FixedSizeCharBuffer(1000);
				LpiExecutorParams lpiParams;
				LpiExecutor* lpiExecutor;

			public:
				LpiExecutor_Tester(const char* lpi, uint8_t noOfLeds = 8) {
					ledConfig.numberOfLEDs = noOfLeds;

					lpiBuffer.LoadFromBuffer(lpi);
					lpiParams.Reset(&lpiBuffer, &ledConfig, &stringProcessor);
				}

				LpiExecutorParams* GetExecutorParams() {
					return &lpiParams;
				}

				bool ValidateOutput(LpiExecutorOutput* output, RI* expectedRIs, int numberOfExpectedRIs) {
					if (output->GetNumberOfRenderingInstructions() != numberOfExpectedRIs) {
						return false;
					}

					RI* actualRIs = output->GetRenderingInstructions();
					for (int i = 0; i < numberOfExpectedRIs; i++) {
						RI expectedRi = expectedRIs[i];
						RI actualRi = actualRIs[i];

						if (expectedRi != actualRi) {
							return false;
						}
					}

					return true;
				}
			};
		}
	}
}
