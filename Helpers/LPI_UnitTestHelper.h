/*!
 * @file LPIInstantiator.h
 *
 * Helper class that instantiates an LPI instance which
 * has all dependencies injected.  The LPI instance is thus
 * ready for unit testing.
 *
 * Written by Kevin White.
 *
 * This file is part of the LS library but should only be used for unit testing.
 *
 */

#pragma once

#include "../../Light Server/src/LPI/LPI.h"

namespace LS {
	class LPI_UnitTestHelper {
		protected:
			uint8_t opcode;
			uint8_t duration;
			uint16_t bufferSize;
			uint16_t noLEDs;
			char* instruction;
		public:
			LPIInstruction* lpiInstruction;
			LEDConfig* ledConfig;
			StringProcessor* stringProcessor;

			/*!
			  @brief   Constructor collects the required values to instantiate the LPI.
			  @param   opcode			 The opcode of the LPI to be instantiated.
			  @param   instruction		 The pointer to the buffer that contains the LPI buffer instruction.
			  @param   duration			 The duration of the LPI in rendering frames.
			  @param   bufferSize		 The size of the buffer to be allocated to contain the LPI buffer instruction.
			  @param   noLEDS			 The number of LEDS.
			*/
			LPI_UnitTestHelper(uint8_t opcode, char* instruction, uint8_t duration = 1, uint16_t bufferSize = 1000, uint16_t noLEDS = 8) {
				this->opcode = opcode;
				this->duration = duration;
				this->bufferSize = bufferSize;
				this->noLEDs = noLEDS;
				this->instruction = instruction;
			}

			/*!
			  @brief   Instantiates a new LPI instance based on the state that was specified
					   during construction.  For example: if opcode 0 was specified then a usable
					   instance of ClearNonAnimatedLPI will be returned.  This is effectively
					   a factory method that instantiates LPI instances that are ready for unit
					   testing purposes.
			  @returns LPI*		A pointer to the instantiated LPI instance.
			*/
			LPI* InstantiateLPI() {
				this->ledConfig = new LEDConfig(noLEDs);
				this->stringProcessor = new StringProcessor();
				FixedSizeCharBuffer* lpiBuffer = new FixedSizeCharBuffer(bufferSize);
				lpiBuffer->LoadFromBuffer(instruction);
				this->lpiInstruction = new LPIInstruction(opcode, duration, lpiBuffer);

				// Instantiate the LPI effect depending on the opcode
				LPI* lpi = nullptr;
				switch (opcode) {
					case 6:
						lpi = new BlocksNonAnimatedLPI(ledConfig, stringProcessor);
						break;
				}

				// Ensure the LPI is initialised fully by resetting the intenral state
				lpi->Reset(this->lpiInstruction);

				return lpi;
			}

			void CleanUp(LPI* lpi) {
				if (this->lpiInstruction != nullptr) {
					if (this->lpiInstruction->lpi != nullptr) free(this->lpiInstruction->lpi);
					free(this->lpiInstruction);
				}

				if (lpi != nullptr) free(lpi);
				if (stringProcessor != nullptr) free(stringProcessor);
				if (ledConfig != nullptr) free(ledConfig);
			}

			/*!
			  @brief   Verifies that an output RI buffer has the expected value.
			  @returns LPI*		A pointer to the instantiated LPI instance.
			*/
			bool VerifyRIBuffer(char* expectedRI, FixedSizeCharBuffer* riBuffer) {
				int areEqual = strcmp(expectedRI, riBuffer->GetBuffer());
				return areEqual == 0;
			}
	};
}