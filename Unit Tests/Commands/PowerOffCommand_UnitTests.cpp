#include "CppUnitTest.h"
#include "../../../Light-Server/src/Commands/PowerOffCommand.h"
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
		TEST_CLASS(PowerOff_ExecuteCommand)
		{
		public:
			TEST_METHOD(WhenExecuted_HttpOkNoContentSent)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				PowerOffCommand command = PowerOffCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get());

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondNoContent));
			}

			TEST_METHOD(WhenExecuted_OrchastorStopProgramsCalled)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				PowerOffCommand command = PowerOffCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get());

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockOrchastor, StopPrograms));
			}

			TEST_METHOD(WhenExecuted_PixelsFilledWith0)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				PowerOffCommand command = PowerOffCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get());

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockPixelController, fill).Using(0, 0, 0));
			}

			TEST_METHOD(WhenExecuted_PixelsShown)
			{
				// arrange
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				PowerOffCommand command = PowerOffCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get());

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockPixelController, show));
			}
		};
	}
}