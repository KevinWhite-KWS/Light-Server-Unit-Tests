#include "CppUnitTest.h"
#include "../../../Light-Server/src/Commands/LoadProgramCommand.h"
#include "../../../Light-Server/src/ValueDomainTypes.h"
#include "../../../Light-Server/src/LightWebServer.h"
#include "../../../Light-Server/src/LPE/Validation/LpJsonValidator.h"
#include "../../../Light-Server/src/LPE/StateBuilder/LpJsonStateBuilder.h"

#include "../../../Light-Server/src/Orchastrator/IOrchastor.h"
#include "../../ExternalDependencies/fakeit.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fakeit;

// fakeit mocking framework: https://github.com/eranpeer/FakeIt

namespace LS {
	namespace Commands {
		class LoadProgramCommand_Stubbed : public LoadProgramCommand {
		public:
			LoadProgramCommand_Stubbed(ILightWebServer* lightWebServer,
				FixedSizeCharBuffer* lpBuffer,
				LpJsonValidator* lpValidator,
				LpJsonStateBuilder* lpStateBuilder,
				LpJsonState* lpState) : LoadProgramCommand(lightWebServer, lpBuffer, lpValidator, lpStateBuilder, lpState) {
			}

			void SetValidateResult(LPValidateCode code) {
				validateResult.ResetResult(code);
			}
		};


		TEST_CLASS(LoadProgram_ExecuteCommand)
		{
		public:
			TEST_METHOD(WhenExecuted_HttpOkNoContentSent)
			{
				// arrange
				char* loadingBuffer = " ";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).AlwaysReturn();
				When(Method(mockLightWebServer, RespondError)).AlwaysReturn();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(loadingBuffer);
				FixedSizeCharBuffer lpBuffer = FixedSizeCharBuffer(1000);
				Mock<LpJsonValidator> mockLpValidator;
				When(Method(mockLpValidator, ValidateLp)).Return();
				Mock<LpJsonStateBuilder> mockLpStateBuilder;
				When(Method(mockLpStateBuilder, BuildState)).Return();
				LpJsonState lpState;
				LoadProgramCommand_Stubbed command = LoadProgramCommand_Stubbed(&mockLightWebServer.get(),
					&lpBuffer,
					&mockLpValidator.get(),
					&mockLpStateBuilder.get(),
					&lpState);
				command.SetValidateResult(LS::LPValidateCode::Valid);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondNoContent));
			}

			TEST_METHOD(WhenExecutedWithInvalidInstruction_HttpErrorSent)
			{
				// arrange
				char* loadingBuffer = " ";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).AlwaysReturn();
				When(Method(mockLightWebServer, RespondError)).AlwaysReturn();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(loadingBuffer);
				FixedSizeCharBuffer lpBuffer = FixedSizeCharBuffer(1000);
				Mock<LpJsonValidator> mockLpValidator;
				When(Method(mockLpValidator, ValidateLp)).Return();
				Mock<LpJsonStateBuilder> mockLpStateBuilder;
				When(Method(mockLpStateBuilder, BuildState)).Return();
				LpJsonState lpState;
				LoadProgramCommand_Stubbed command = LoadProgramCommand_Stubbed(&mockLightWebServer.get(),
					&lpBuffer,
					&mockLpValidator.get(),
					&mockLpStateBuilder.get(),
					&lpState);
				command.SetValidateResult(LS::LPValidateCode::InvalidInstruction);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondError));
			}

			TEST_METHOD(WhenExecutedWithNoInstructions_HttpErrorSent)
			{
				// arrange
				char* loadingBuffer = " ";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).AlwaysReturn();
				When(Method(mockLightWebServer, RespondError)).AlwaysReturn();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(loadingBuffer);
				FixedSizeCharBuffer lpBuffer = FixedSizeCharBuffer(1000);
				Mock<LpJsonValidator> mockLpValidator;
				When(Method(mockLpValidator, ValidateLp)).Return();
				Mock<LpJsonStateBuilder> mockLpStateBuilder;
				When(Method(mockLpStateBuilder, BuildState)).Return();
				LpJsonState lpState;
				LoadProgramCommand_Stubbed command = LoadProgramCommand_Stubbed(&mockLightWebServer.get(),
					&lpBuffer,
					&mockLpValidator.get(),
					&mockLpStateBuilder.get(),
					&lpState);
				command.SetValidateResult(LS::LPValidateCode::NoIntructions);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondError));
			}

			TEST_METHOD(WhenExecuted_LpStateIsBuilt)
			{
				// arrange
				char* loadingBuffer = " ";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).AlwaysReturn();
				When(Method(mockLightWebServer, RespondError)).AlwaysReturn();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(loadingBuffer);
				FixedSizeCharBuffer lpBuffer = FixedSizeCharBuffer(1000);
				Mock<LpJsonValidator> mockLpValidator;
				When(Method(mockLpValidator, ValidateLp)).Return();
				Mock<LpJsonStateBuilder> mockLpStateBuilder;
				When(Method(mockLpStateBuilder, BuildState)).Return();
				LpJsonState lpState;
				LoadProgramCommand_Stubbed command = LoadProgramCommand_Stubbed(&mockLightWebServer.get(),
					&lpBuffer,
					&mockLpValidator.get(),
					&mockLpStateBuilder.get(),
					&lpState);
				command.SetValidateResult(LS::LPValidateCode::Valid);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLpStateBuilder, BuildState));
			}

			TEST_METHOD(WhenExecuted_LpIsValidated)
			{
				// arrange
				char* loadingBuffer = " ";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).AlwaysReturn();
				When(Method(mockLightWebServer, RespondError)).AlwaysReturn();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(loadingBuffer);
				FixedSizeCharBuffer lpBuffer = FixedSizeCharBuffer(1000);
				Mock<LpJsonValidator> mockLpValidator;
				When(Method(mockLpValidator, ValidateLp)).Return();
				Mock<LpJsonStateBuilder> mockLpStateBuilder;
				When(Method(mockLpStateBuilder, BuildState)).Return();
				LpJsonState lpState;
				LoadProgramCommand_Stubbed command = LoadProgramCommand_Stubbed(&mockLightWebServer.get(),
					&lpBuffer,
					&mockLpValidator.get(),
					&mockLpStateBuilder.get(),
					&lpState);
				command.SetValidateResult(LS::LPValidateCode::Valid);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLpValidator, ValidateLp));
			}
		};
	}
}