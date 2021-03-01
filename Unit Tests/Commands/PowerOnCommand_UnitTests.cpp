#include "CppUnitTest.h"
#include "../../../Light-Server/src/Commands/PowerOnCommand.h"
#include "../../../Light-Server/src/ValueDomainTypes.h"
#include "../../../Light-Server/src/LightWebServer.h"
#include "../../../Light-Server/src/StringProcessor.h"

#include "../../../Light-Server/src/Orchastrator/IOrchastor.h"
#include "../../ExternalDependencies/fakeit.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fakeit;

// fakeit mocking framework: https://github.com/eranpeer/FakeIt

namespace LS {
	namespace Commands {
		TEST_CLASS(PowerOn_ExecuteCommand)
		{
		public:
			TEST_METHOD(WhenExecuted_HttpOkNoContentSent)
			{
				// arrange
				char loadingBuffer[] = "";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).Return(loadingBuffer);
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).AlwaysReturn();
				When(Method(mockPixelController, show)).AlwaysReturn();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				Mock<StringProcessor> mockStringProcessor;
				When(Method(mockStringProcessor, ExtractColourFromHexEncoded)).Return(Colour(0,0,0));
				PowerOnCommand command = PowerOnCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get(), &mockStringProcessor.get());

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondNoContent));
			}

			TEST_METHOD(WhenExecuted_OrchastorStopProgramsCalled)
			{
				// arrange
				char loadingBuffer[] = "";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).Return(loadingBuffer);
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).AlwaysReturn();
				When(Method(mockPixelController, show)).AlwaysReturn();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				Mock<StringProcessor> mockStringProcessor;
				When(Method(mockStringProcessor, ExtractColourFromHexEncoded)).Return(Colour(0, 0, 0));
				PowerOnCommand command = PowerOnCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get(), &mockStringProcessor.get());

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockOrchastor, StopPrograms));
			}

			TEST_METHOD(WhenExecuted_PixelsShown)
			{
				// arrange
				char loadingBuffer[] = "";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).Return(loadingBuffer);
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).AlwaysReturn();
				When(Method(mockPixelController, show)).AlwaysReturn();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				Mock<StringProcessor> mockStringProcessor;
				When(Method(mockStringProcessor, ExtractColourFromHexEncoded)).Return(Colour(0, 0, 0));
				PowerOnCommand command = PowerOnCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get(), &mockStringProcessor.get());

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockPixelController, show));
			}

			TEST_METHOD(WhenExecutedWithNoColourSpecified_PixelsSetToWhite)
			{
				// arrange
				char loadingBuffer[] = "";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).Return(loadingBuffer);
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).AlwaysReturn();
				When(Method(mockPixelController, show)).AlwaysReturn();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				Mock<StringProcessor> mockStringProcessor;
				When(Method(mockStringProcessor, ExtractColourFromHexEncoded)).Return(Colour(0, 0, 0));
				PowerOnCommand command = PowerOnCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get(), &mockStringProcessor.get());

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockPixelController, fill).Using(16777215, 0, 0)).Exactly(Once);
			}

			TEST_METHOD(WhenExecutedwithBlackColour_PixelsSetToBlack)
			{
				// arrange
				char loadingBuffer[] = "000000";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).Return(loadingBuffer);
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).AlwaysReturn();
				When(Method(mockPixelController, show)).AlwaysReturn();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				Mock<StringProcessor> mockStringProcessor;
				When(Method(mockStringProcessor, ExtractColourFromHexEncoded)).Return(Colour(0, 0, 0));
				PowerOnCommand command = PowerOnCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get(), &mockStringProcessor.get());

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockPixelController, fill).Using(0, 0, 0)).Exactly(Once);
			}

			TEST_METHOD(WhenExecutedwithRedColour_PixelsSetToRed)
			{
				// arrange
				char loadingBuffer[] = "FF0000";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).Return(loadingBuffer);
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).AlwaysReturn();
				When(Method(mockPixelController, show)).AlwaysReturn();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				StringProcessor stringProcessor;	// we have to use a real instance because the isValid param
				PowerOnCommand command = PowerOnCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get(), &stringProcessor);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockPixelController, fill).Using(16711680, 0, 0)).Exactly(Once);
			}

			TEST_METHOD(WhenExecutedWithRandomColour_PixelsSet)
			{
				// arrange
				char loadingBuffer[] = "AAB2C0";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).Return(loadingBuffer);
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).AlwaysReturn();
				When(Method(mockPixelController, show)).AlwaysReturn();
				Mock<IOrchastor> mockOrchastor;
				When(Method(mockOrchastor, StopPrograms)).Return();
				StringProcessor stringProcessor;	// we have to use a real instance because the isValid param
				PowerOnCommand command = PowerOnCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get(), &stringProcessor);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockPixelController, fill).Using(11186880, 0, 0)).Exactly(Once);
			}
		};
	}
}