#include "CppUnitTest.h"
#include "../../../Light-Server/src/Commands/GetAboutCommand.h"
#include "../../../Light-Server/src/ValueDomainTypes.h"
#include "../../mocks/Mock_WebServer.h"
#include "../../../Light-Server/src/LightWebServer.h"

#include "../../../Light-Server/src/Orchastrator/IOrchastor.h"
#include "../../ExternalDependencies/fakeit.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fakeit;

// fakeit mocking framework: https://github.com/eranpeer/FakeIt

namespace LS {
	namespace Commands {
		TEST_CLASS(GetAboutCommand_ExecuteCommand)
		{
		public:
			TEST_METHOD(WhenExecuted_HttpOKSent)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondOK)).Return();
				StaticJsonDocument<1000> webDoc;
				FixedSizeCharBuffer webResponse = FixedSizeCharBuffer(1000);
				LEDConfig ledConfig = LEDConfig(8);
				GetAboutCommand command = GetAboutCommand(&mockLightWebServer.get(), &webDoc, &webResponse, &ledConfig);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondOK));
			}

			TEST_METHOD(WhenExecutedWith8Pixels_CorrectResponseSent)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondOK)).Return();
				StaticJsonDocument<1000> webDoc;
				FixedSizeCharBuffer webResponse = FixedSizeCharBuffer(1000);
				LEDConfig ledConfig = LEDConfig(8);
				GetAboutCommand command = GetAboutCommand(&mockLightWebServer.get(), &webDoc, &webResponse, &ledConfig);

				// act
				command.ExecuteCommand();

				// assert
				int areEqual = strcmp("{\r\n  \"LEDs\": 8,\r\n  \"LS Version\": \"1.0.0\",\r\n  \"LDL Version\": \"1.0.0\"\r\n}", webResponse.GetBuffer());
				Assert::AreEqual<int>(0, areEqual);
			}

			TEST_METHOD(WhenExecutedWith50Pixels_CorrectResponseSent)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondOK)).Return();
				StaticJsonDocument<1000> webDoc;
				FixedSizeCharBuffer webResponse = FixedSizeCharBuffer(1000);
				LEDConfig ledConfig = LEDConfig(50);
				GetAboutCommand command = GetAboutCommand(&mockLightWebServer.get(), &webDoc, &webResponse, &ledConfig);

				// act
				command.ExecuteCommand();

				// assert
				int areEqual = strcmp("{\r\n  \"LEDs\": 50,\r\n  \"LS Version\": \"1.0.0\",\r\n  \"LDL Version\": \"1.0.0\"\r\n}", webResponse.GetBuffer());
				Assert::AreEqual<int>(0, areEqual);
			}
		};
	}
}