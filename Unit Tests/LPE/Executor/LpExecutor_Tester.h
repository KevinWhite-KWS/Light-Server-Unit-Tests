#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/LpJsonStateBuilder.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/JsonInstructionBuilderFactory.h"

#include "../../../../Light-Server/src/LPE/StateBuilder/LpJsonState.h";
#include "../../../../Light-Server/src/StringProcessor.h"
#include "../../../../Light-Server/src/LPE/Executor/LpExecutor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace LPE {
		namespace Executor {
			/*!
				@brief		Provides a test hardness to functionally
							test the execution of Light Programs.
				@author		Kevin White
				@date		31 Dec 2020
			*/
			class LpExecutor_Tester {
			private:
				char** expectedExecutionOutput;
				int numberOfExpectedExecutionOutputs;

			public:
				FixedSizeCharBuffer renderingBuffer = FixedSizeCharBuffer(1000);
				LpiExecutorOutput lpiOutput;

				LpExecutor_Tester(char** expectedExecutionOutput, int numberOfExpectedExecutionOutputs) {
					this->expectedExecutionOutput = expectedExecutionOutput;
					this->numberOfExpectedExecutionOutputs = numberOfExpectedExecutionOutputs;
				}

				/*!
					@brief		Tests the passed Light Program returns the rendering instructions
								as defined in the collection of strings in expectedExecutionOutput.
					@param		lp		A pointer to the Light Program to be tested.
					@returns	If the output is as expected then nullptr.  Otheriwse, a pointer to
								the expectedExecutionOutput string that failed.
					@author		Kevin White
					@date		31 Dec 2020
				*/
				char* TestExecutor(char* lp) {

					// load the light program state
					LpJsonState state;
					LEDConfig ledConfig(8);
					StringProcessor stringProcessor;
					// LPIFactory lpiFactory(&ledConfig, &stringProcessor);
					LpiExecutorFactory lpiExecutorFactory;
					JsonInstructionBuilderFactory instructionBuilderFactory(&lpiExecutorFactory, &stringProcessor, &ledConfig);
					LpJsonStateBuilder stateBuilder(&instructionBuilderFactory);
					FixedSizeCharBuffer lpBuffer(1000);
					lpBuffer.LoadFromBuffer(lp);
					stateBuilder.BuildState(&lpBuffer, &state);

					// this is the class under test
					LpExecutor executor(&lpiExecutorFactory, &stringProcessor, &ledConfig);

					int frameCounter = 1;
					bool continueExecution = true;
					char* currentExpectedExecutionOutput = expectedExecutionOutput[0];
					int currentExpectedExecutionOutputIndex = 0;
					char outputStatementIndex[4];

					while (continueExecution) {
						// execute the LP
						executor.Execute(&state, &lpiOutput);

						// is this execution cycle one of the statements we need
						// to verify?
						strncpy(outputStatementIndex, currentExpectedExecutionOutput, 3);
						int outputStatementIndexi = atoi(outputStatementIndex);

						if (outputStatementIndexi == frameCounter) {
							renderingBuffer.ClearBuffer();

							// convert the RIs to strings
							if (lpiOutput.GetNumberOfRenderingInstructions() > 0) {
								RI* renIns = lpiOutput.GetRenderingInstructions();
								char* renderingBufferBuf = renderingBuffer.GetBuffer();

								for (int i = 0; i < lpiOutput.GetNumberOfRenderingInstructions(); i++) {
									RI renIn = renIns[i];

									stringProcessor.ConvertNumberToHexEncoded(renderingBufferBuf, renIn.colour.red);
									renderingBufferBuf += 2;
									stringProcessor.ConvertNumberToHexEncoded(renderingBufferBuf, renIn.colour.green);
									renderingBufferBuf += 2;
									stringProcessor.ConvertNumberToHexEncoded(renderingBufferBuf, renIn.colour.blue);
									renderingBufferBuf += 2;
									stringProcessor.ConvertNumberToHexEncoded(renderingBufferBuf, renIn.number);
									renderingBufferBuf += 2;
								}

								if (lpiOutput.GetRepeatRenderingInstructions()) {
									// repeat
									*renderingBufferBuf = 'R';
								}
							}


							if (strcmp(currentExpectedExecutionOutput + 4, renderingBuffer.GetBuffer()) != 0) {
								// expected output is not output, so test fails
								return currentExpectedExecutionOutput;
							}

							if (currentExpectedExecutionOutputIndex <= numberOfExpectedExecutionOutputs) {
								currentExpectedExecutionOutput = expectedExecutionOutput[++currentExpectedExecutionOutputIndex];
							}
						}

						if (frameCounter >= numberOfExpectedExecutionOutputs) {
							continueExecution = false;
						}

						frameCounter++;
					}

					return nullptr;
				}
			};
		}
	}
}
