#include "CppUnitTest.h"
#include "../../../Light-Server/src/Commands/InvalidCommand.h"
#include "../../../Light-Server/src/ValueDomainTypes.h"
#include "../../mocks/Mock_WebServer.h"
#include "../../../Light-Server/src/LightWebServer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LS {
	namespace Commands {
		TEST_CLASS(InvalidCommand_ExecuteCommand)
		{
		public:
			TEST_METHOD(WhenExecuted_HttpFailSent)
			{
				// arrange
				FixedSizeCharBuffer loadingBuffer(1000);
				Mock_WebServer mockWebServer = Mock_WebServer();
				Mock_LightWebServer mockLightWebServer = Mock_LightWebServer(&mockWebServer, &loadingBuffer);
				ILightWebServer* lightWebServer = (ILightWebServer*)&mockLightWebServer;
				InvalidCommand command = InvalidCommand(lightWebServer);

				// act
				command.ExecuteCommand();

				// assert
				Assert::IsTrue(mockWebServer.httpFailCalled);
			}

			TEST_METHOD(WhenExecuted_TrueReturned)
			{
				// arrange
				FixedSizeCharBuffer loadingBuffer(1000);
				Mock_WebServer mockWebServer = Mock_WebServer();
				Mock_LightWebServer mockLightWebServer = Mock_LightWebServer(&mockWebServer, &loadingBuffer);
				ILightWebServer* lightWebServer = (ILightWebServer*)&mockLightWebServer;
				InvalidCommand command = InvalidCommand(lightWebServer);

				// act
				bool executed = command.ExecuteCommand();

				// assert
				Assert::IsTrue(executed);
			}
		};
	}
}