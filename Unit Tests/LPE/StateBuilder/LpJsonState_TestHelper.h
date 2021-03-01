#include "CppUnitTest.h"
#include "../../../../Light-Server/src/LPE/StateBuilder/LpJsonStateBuilder.h"

namespace LS {
	namespace LPE {
		namespace StateBuilder {
			/*!
				@brief		Provides helper methods to verify the state
							of a LpJsonState instance.
				@author		Kevin White
				@date		27 Dec 2020
			*/
			class LpJsonState_TestHelper : public LpJsonState {
			private:
				/*!
					@brief	Verifies that the current instruction represents an
							LPI and that the LPI contains the expected instruction string.
					@param	currentInstruction		A pointer to the current instruction in the tree.
					@param	verificationStatement	A pointer to the string that contains the expected instruction string.
					@returns	True if the LPI is as expected or false otherwise.
					@author	Kevin White
					@date	27 Dec 2020
				*/
				bool VerifyLpi(Instruction* currentInstruction, char* verificationStatement) {
					LpInstruction* lpIns = dynamic_cast<LpInstruction*>(currentInstruction);

					if (lpIns == nullptr) {
						return false;
					}

					if (strcmp(lpIns->getLpi(), verificationStatement + 2) != 0) {
						return false;
					}

					return true;
				}

				/*!
					@brief	Verifies that the current instruction represents a repeat
							and that the repeat has the expected number of iterations.
					@param	currentInstruction		A pointer to the current instruction in the tree.
					@param	verificationStatement	A pointer to the string that contains the expected number of iterations.
					@returns	True if the repeat is as expected or false otherwise.
					@author	Kevin White
					@date	27 Dec 2020
				*/
				bool VerifyRepeat(Instruction* currentInstruction, char* verificationStatement) {
					// verify that the current instructions points to a RepeatInstruction instance
					// which has the expected number of iterations
					RepeatInstruction* repeatIns = dynamic_cast<RepeatInstruction*>(currentInstruction);

					if (repeatIns == nullptr) {
						return false;
					}

					int numIterationsRequired = atoi(verificationStatement + 2);
					if (numIterationsRequired != repeatIns->getRemainingIterations()) {
						return false;
					}

					return true;
				}

				/*!
					@brief	Verifies that the current instruction is valid according
							to the what is specified in the given verificationStatement string.
					@param	currentInstruction		A pointer to the current instruction in the tree.
					@param	verificationStatement	A pointer to the string that contains the details of what is expected
													in the current instruction.
					@returns	True if the instruction is as expected or false otherwise.
					@author	Kevin White
					@date	27 Dec 2020
				*/
				bool VerifyInstruction(Instruction* currentInstruction, char* verificationStatement) {
					bool insVerified = false;

					switch (*verificationStatement) {
					case 'I':
						insVerified = VerifyLpi(currentInstruction, verificationStatement);
						break;
					case 'R':
						insVerified = VerifyRepeat(currentInstruction, verificationStatement);
						break;
					}

					return insVerified;
				}

				/*!
					@brief	Performs a tree navigation by moving the current instruction to either: 'n' - no further
							instructions, 'N' - next sibling, 'C' - first child, or 'P' - parent.  Effectively
							we are performing a manual nagivation in order to verify that the expected tree
							representation has been built.
					@param	verificationStatement	A pointer to the string that a character which tells us what type
													of navigation is expected.
					@param	currentInstruction		A pointer to the current instruction in the tree.
					@param	successful				A pointer to a boolean which will be set to true if the
													navigation was successful - as specified - or false if the
													navigation could not be performed.
					@returns	A pointer to the newly navigated instruction in the tree.
					@author	Kevin White
					@date	27 Dec 2020
				*/
				Instruction* NavigateToNextInstruction(char* verificationStatement, Instruction* currentInstruction, bool* successful) {
					*successful = false;

					switch (*(verificationStatement + 1)) {
					case 'n':
						// 'n' means null, so next instruction should be a nullptr
						currentInstruction = currentInstruction->getNext();
						if (currentInstruction == nullptr) {
							*successful = true;
						}

						return nullptr;
						break;
					case 'N':
						// 'N' means next, so there should be a sibling instruction
						currentInstruction = currentInstruction->getNext();
						break;
					case 'C':
						// 'C' means child, so there should be a child instruction (i.e.
						// this is a repeat)
						currentInstruction = ((InstructionWithChild*)currentInstruction)->getFirstChild();
						break;
					case 'P':
						// 'P' means parent, so there should be a parent instruction
						currentInstruction = currentInstruction->getParent();
						break;
					}

					if (currentInstruction != nullptr) {
						*successful = true;
					}

					return currentInstruction;
				}

			public:
				
				/*!
					@brief	Verifies the state that has been built is the state is expected
							to be have been built.  This is achieved by supplying a collection
							of verification statements.  Each statement provides the specification
							of what the instruction is supposed to represent and how the next instruction
							is to be navigated (next, child, parent, or null).
							
							A single verification statement has the following format:

							{Ins type}{Navigate ins}{Ins details}

							{Ins type} has one of type values:
								I = the instruction is expected to be an LPI
								R = the instruction is expected to be a repeat
							{Navigate ins} has four vaues:
								n = NULL - no further navigation expected, so the 'next' sibling should null
								N = next - the next instruction is the next sibling
								C = child - the next instruction is the first child (i.e. of a repeat)
								P = parent - the next instruction is the parent
							{Ins details} will be a valid LPI string if {Ins type} is I or otherwise
							the expected number of iterations if the {Ins type} is R.
					@param	verificationStatements		The collection of verification statements
					@param	numVerificationStatements	The number of verificationStatements
					@returns	nullptr if verification was successful or otherwise a pointer to the verification
								statement that caused verification to fail.
					@author	Kevin White
					@date	27 Dec 2020
				*/
				char* VerifyState(char** verificationStatements, int numVerificationStatements) {
					int instructionIndex = 0;
					int repeatIndex = 0;
					Instruction* currentInstruction = LpJsonState::getFirstInstruction();

					for (int i = 0; i < numVerificationStatements; i++) {
						char* verificationStatement = verificationStatements[i];

						bool insVerified = VerifyInstruction(currentInstruction, verificationStatement);
						if (!insVerified) {
							return verificationStatement;
						}

						// now, navigate depending on the navigation instruction
						bool successfulNavigation = false;
						currentInstruction = NavigateToNextInstruction(verificationStatement, currentInstruction, &successfulNavigation);
						if (!successfulNavigation) {
							return verificationStatement;
						}
					}

					return nullptr;
				}
			};
		}
	}
}