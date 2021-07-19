#include "CppUnitTest.h"
#include "../../../Light-Server/src/Commands/SetLedsCommand.h"
#include "../../../Light-Server/src/ValueDomainTypes.h"
#include "../../mocks/Mock_WebServer.h"
#include "../../../Light-Server/src/LightWebServer.h"
#include "../../../Light-Server/src/StringProcessor.h"
#include "../../../Light-Server/src/ConfigPersistance/IConfigPersistance.h"
#include "../../../Light-Server/src/LPE/StateBuilder/LpState.h"

#include "../../../Light-Server/src/Orchastrator/IOrchastor.h"
#include "../../ExternalDependencies/fakeit.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fakeit;

// fakeit mocking framework: https://github.com/eranpeer/FakeIt

#define BUFFER_JSON_RESPONSE_SIZE	200
#define NUM_LEDS					8

namespace LS {
	namespace Commands {
		TEST_CLASS(SetLeds_ExecuteCommand)
		{
		public:
			TEST_METHOD(WhenExecuted_HttpOkNoContentSent)
			{
				// arrange
				char* webBuffer = "32";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(webBuffer);
				StringProcessor stringProcessor;
				LEDConfig ledConfig;
				ledConfig.numberOfLEDs = NUM_LEDS;
				Mock<IConfigPersistance> mockConfigPersistance;
				When(Method(mockConfigPersistance, SaveConfig)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				When(Method(mockPixelController, updateLength)).Return();
				LpState state;
				SetLedsCommand command = SetLedsCommand(
					&mockLightWebServer.get(),
					&stringProcessor,
					&ledConfig,
					&mockConfigPersistance.get(),
					&mockPixelController.get(),
					&state
				);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondNoContent));
			}

			TEST_METHOD(WhenExecutedPixelsIs9_HttpErrorSent)
			{
				// arrange
				char* webBuffer = "09";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, RespondError)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(webBuffer);
				StringProcessor stringProcessor;
				LEDConfig ledConfig;
				ledConfig.numberOfLEDs = NUM_LEDS;
				Mock<IConfigPersistance> mockConfigPersistance;
				When(Method(mockConfigPersistance, SaveConfig)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				When(Method(mockPixelController, updateLength)).Return();
				LpState state;
				SetLedsCommand command = SetLedsCommand(
					&mockLightWebServer.get(),
					&stringProcessor,
					&ledConfig,
					&mockConfigPersistance.get(),
					&mockPixelController.get(),
					&state
				);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondError));
			}

			TEST_METHOD(WhenExecutedPixelsIs201_HttpErrorSent)
			{
				// arrange
				char* webBuffer = "C9";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, RespondError)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(webBuffer);
				StringProcessor stringProcessor;
				LEDConfig ledConfig;
				ledConfig.numberOfLEDs = NUM_LEDS;
				Mock<IConfigPersistance> mockConfigPersistance;
				When(Method(mockConfigPersistance, SaveConfig)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				When(Method(mockPixelController, updateLength)).Return();
				LpState state;
				SetLedsCommand command = SetLedsCommand(
					&mockLightWebServer.get(),
					&stringProcessor,
					&ledConfig,
					&mockConfigPersistance.get(),
					&mockPixelController.get(),
					&state
				);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondError));
			}

			TEST_METHOD(WhenExecutedPixelsIs200_HttpOkNoContentSent)
			{
				// arrange
				char* webBuffer = "C8";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, RespondError)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(webBuffer);
				StringProcessor stringProcessor;
				LEDConfig ledConfig;
				ledConfig.numberOfLEDs = NUM_LEDS;
				Mock<IConfigPersistance> mockConfigPersistance;
				When(Method(mockConfigPersistance, SaveConfig)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				When(Method(mockPixelController, updateLength)).Return();
				LpState state;
				SetLedsCommand command = SetLedsCommand(
					&mockLightWebServer.get(),
					&stringProcessor,
					&ledConfig,
					&mockConfigPersistance.get(),
					&mockPixelController.get(),
					&state
				);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondNoContent));
			}

			TEST_METHOD(WhenExecutedPixelsIs10_HttpOkNoContentSent)
			{
				// arrange
				char* webBuffer = "0A";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, RespondError)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(webBuffer);
				StringProcessor stringProcessor;
				LEDConfig ledConfig;
				ledConfig.numberOfLEDs = NUM_LEDS;
				Mock<IConfigPersistance> mockConfigPersistance;
				When(Method(mockConfigPersistance, SaveConfig)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				When(Method(mockPixelController, updateLength)).Return();
				LpState state;
				SetLedsCommand command = SetLedsCommand(
					&mockLightWebServer.get(),
					&stringProcessor,
					&ledConfig,
					&mockConfigPersistance.get(),
					&mockPixelController.get(),
					&state
				);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockLightWebServer, RespondNoContent));
			}

			TEST_METHOD(WhenExecutedPixelsIs10_NewNumberOfPixelsSavedToPersistantStorage)
			{
				// arrange
				char* webBuffer = "0A";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, RespondError)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(webBuffer);
				StringProcessor stringProcessor;
				LEDConfig ledConfig;
				ledConfig.numberOfLEDs = NUM_LEDS;
				Mock<IConfigPersistance> mockConfigPersistance;
				When(Method(mockConfigPersistance, SaveConfig)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				When(Method(mockPixelController, updateLength)).Return();
				LpState state;
				SetLedsCommand command = SetLedsCommand(
					&mockLightWebServer.get(),
					&stringProcessor,
					&ledConfig,
					&mockConfigPersistance.get(),
					&mockPixelController.get(),
					&state
				);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockConfigPersistance, SaveConfig).Using(&ledConfig)).Exactly(Once);
				Assert::AreEqual<uint8_t>(10, ledConfig.numberOfLEDs);
			}

			TEST_METHOD(WhenExecutedPixelsIs10_StateIsReset)
			{
				// arrange
				char* webBuffer = "0A";
				Mock<ILightWebServer> mockLightWebServer;
				When(Method(mockLightWebServer, RespondNoContent)).Return();
				When(Method(mockLightWebServer, RespondError)).Return();
				When(Method(mockLightWebServer, GetLoadingBuffer)).AlwaysReturn(webBuffer);
				StringProcessor stringProcessor;
				LEDConfig ledConfig;
				ledConfig.numberOfLEDs = NUM_LEDS;
				Mock<IConfigPersistance> mockConfigPersistance;
				When(Method(mockConfigPersistance, SaveConfig)).Return();
				Mock<IPixelController> mockPixelController;
				When(Method(mockPixelController, fill)).Return();
				When(Method(mockPixelController, show)).Return();
				When(Method(mockPixelController, updateLength)).Return();
				// LpState state;
				Mock<LpState> mockState;
				When(Method(mockState, reset)).Return();

				SetLedsCommand command = SetLedsCommand(
					&mockLightWebServer.get(),
					&stringProcessor,
					&ledConfig,
					&mockConfigPersistance.get(),
					&mockPixelController.get(),
					&mockState.get()
				);

				// act
				command.ExecuteCommand();

				// assert
				Verify(Method(mockState, reset)).Exactly(Once);
			}
		};
	}
}