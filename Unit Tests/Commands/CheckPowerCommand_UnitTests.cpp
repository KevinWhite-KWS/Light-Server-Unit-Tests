#include "CppUnitTest.h"
#include "../../../Light-Server/src/Commands/CheckPowerCommand.h"
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
		TEST_CLASS(CheckPower_ExecuteCommand)
		{
		public:
			TEST_METHOD(WhenExecuted_HttpOKSent)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondOK)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, numPixels)).AlwaysReturn(8);
				When(Method(mockPixelController, getPixelColor)).AlwaysReturn(0);
				StaticJsonDocument<1000> webDoc;
				FixedSizeCharBuffer webResponse = FixedSizeCharBuffer(1000);
				CheckPowerCommand command = CheckPowerCommand(&mockLightWebServer.get(), &mockPixelController.get(), &webDoc, &webResponse);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondOK));
			}

			TEST_METHOD(WhenExecutedNoPixelsOn_CorrectReponseSent)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondOK)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, numPixels)).AlwaysReturn(8);
				When(Method(mockPixelController, getPixelColor)).AlwaysReturn(0);
				StaticJsonDocument<1000> webDoc;
				FixedSizeCharBuffer webResponse = FixedSizeCharBuffer(1000);
				CheckPowerCommand command = CheckPowerCommand(&mockLightWebServer.get(), &mockPixelController.get(), &webDoc, &webResponse);

				// act
				command.ExecuteCommand();

				// assert
				int areEqual = strcmp("{\r\n  \"power\": \"off\"\r\n}", webResponse.GetBuffer());
				Assert::AreEqual<int>(0, areEqual);
			}

			TEST_METHOD(WhenExecutedPixels255_CorrectReponseSent)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondOK)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, numPixels)).AlwaysReturn(8);
				When(Method(mockPixelController, getPixelColor)).AlwaysReturn(255);
				StaticJsonDocument<1000> webDoc;
				FixedSizeCharBuffer webResponse = FixedSizeCharBuffer(1000);
				CheckPowerCommand command = CheckPowerCommand(&mockLightWebServer.get(), &mockPixelController.get(), &webDoc, &webResponse);

				// act
				command.ExecuteCommand();

				// assert
				int areEqual = strcmp("{\r\n  \"power\": \"on\"\r\n}", webResponse.GetBuffer());
				Assert::AreEqual<int>(0, areEqual);
			}

			TEST_METHOD(WhenExecutedPixels1_CorrectReponseSent)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondOK)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, numPixels)).AlwaysReturn(8);
				When(Method(mockPixelController, getPixelColor)).AlwaysReturn(255);
				StaticJsonDocument<1000> webDoc;
				FixedSizeCharBuffer webResponse = FixedSizeCharBuffer(1000);
				CheckPowerCommand command = CheckPowerCommand(&mockLightWebServer.get(), &mockPixelController.get(), &webDoc, &webResponse);

				// act
				command.ExecuteCommand();

				// assert
				int areEqual = strcmp("{\r\n  \"power\": \"on\"\r\n}", webResponse.GetBuffer());
				Assert::AreEqual<int>(0, areEqual);
			}
		};
	}
}