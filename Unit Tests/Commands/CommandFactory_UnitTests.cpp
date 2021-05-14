#include "CppUnitTest.h"
#include "../../../Light-Server/src/Commands/CommandFactory.h"
#include "../../../Light-Server/src/ValueDomainTypes.h"
#include "../../../Light-Server/src/LightWebServer.h"
#include "../../../Light-Server/src/LPE/Validation/LpJsonValidator.h"
#include "../../../Light-Server/src/LPE/StateBuilder/LpJsonStateBuilder.h"
#include "../../../Light-Server/src/Orchastrator/IOrchastor.h"
#include "../../../Light-Server/src/ConfigPersistance/IConfigPersistance.h"

#include "../../ExternalDependencies/fakeit.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fakeit;

// fakeit mocking framework: https://github.com/eranpeer/FakeIt

namespace LS {
	namespace Commands {
		class CommandFactoryTestingHelper {
		private:
			CommandFactory* commandFactory;

		public:
			CommandFactoryTestingHelper() {
				Mock<ILightWebServer> mockLightWebServer;
				FixedSizeCharBuffer lpBuffer = FixedSizeCharBuffer(1000);
				Mock<LpJsonValidator> mockValidator;
				Mock<LpJsonStateBuilder> mockStateBuilder;
				LpJsonState state;
				Mock<IOrchastor> mockOrchastor;
				Mock<IPixelController> mockPixelController;
				StringProcessor stringProcessor;
				StaticJsonDocument<1000> webDoc;
				FixedSizeCharBuffer webResponse = FixedSizeCharBuffer(1000);
				Mock<IConfigPersistance> mockConfigPersistance;
				LEDConfig ledConfig = LEDConfig(8);
				commandFactory = new CommandFactory();

				NoAuthCommand noAuthCommand = NoAuthCommand(&mockLightWebServer.get());
				InvalidCommand invalidCommand = InvalidCommand(&mockLightWebServer.get());
				LoadProgramCommand loadProgramCommand = LoadProgramCommand(&mockLightWebServer.get(), &lpBuffer, &mockValidator.get(), &mockStateBuilder.get(), &state);
				PowerOffCommand powerOffCommand = PowerOffCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get());
				PowerOnCommand powerOnCommand = PowerOnCommand(&mockLightWebServer.get(), &mockPixelController.get(), &mockOrchastor.get(), &stringProcessor);
				CheckPowerCommand checkPowerCommand = CheckPowerCommand(&mockLightWebServer.get(), &mockPixelController.get(), &webDoc, &webResponse);
				GetAboutCommand getAboutCommand = GetAboutCommand(&mockLightWebServer.get(), &webDoc, &webResponse, &ledConfig);
				SetLedsCommand setLedsCommand = SetLedsCommand(&mockLightWebServer.get(), &stringProcessor, &ledConfig, &mockConfigPersistance.get(), &mockPixelController.get());

				commandFactory->SetCommand(CommandType::NOAUTH, &noAuthCommand);
				commandFactory->SetCommand(CommandType::INVALID, &invalidCommand);
				commandFactory->SetCommand(CommandType::LOADPROGRAM, &loadProgramCommand);
				commandFactory->SetCommand(CommandType::POWEROFF, &powerOffCommand);
				commandFactory->SetCommand(CommandType::POWERON, &powerOnCommand);
				commandFactory->SetCommand(CommandType::CHECKPOWER, &checkPowerCommand);
				commandFactory->SetCommand(CommandType::GETABOUT, &getAboutCommand);
				commandFactory->SetCommand(CommandType::SETLEDS, &setLedsCommand);
			}

			~CommandFactoryTestingHelper() {
				free(commandFactory);
			}

			CommandFactory* GetCommandFactory() {
				return commandFactory;
			}
		};

		TEST_CLASS(CommandFactory_GetCommand)
		{
		public:
			TEST_METHOD(WhenExecutedWithNoAuthRequested_NoAuthCommandReturned)
			{
				// arrange
				CommandFactoryTestingHelper commandFactoryHelper;
				CommandFactory* factory = commandFactoryHelper.GetCommandFactory();

				// act
				ICommand* command = factory->GetCommand(CommandType::NOAUTH);

				// assert
				NoAuthCommand* noAuthCommand = dynamic_cast<NoAuthCommand*>(command);
				Assert::IsNotNull(noAuthCommand);
			}

			TEST_METHOD(WhenExecutedWithInvalidRequested_InvalidCommandReturned)
			{
				// arrange
				CommandFactoryTestingHelper commandFactoryHelper;
				CommandFactory* factory = commandFactoryHelper.GetCommandFactory();

				// act
				ICommand* command = factory->GetCommand(CommandType::INVALID);

				// assert
				InvalidCommand* invalidCommand = dynamic_cast<InvalidCommand*>(command);
				Assert::IsNotNull(invalidCommand);
			}

			TEST_METHOD(WhenExecutedWithLoadProgramRequested_LoadProgramCommandReturned)
			{
				// arrange
				CommandFactoryTestingHelper commandFactoryHelper;
				CommandFactory* factory = commandFactoryHelper.GetCommandFactory();

				// act
				ICommand* command = factory->GetCommand(CommandType::LOADPROGRAM);

				// assert
				LoadProgramCommand* loadProgramCommand = dynamic_cast<LoadProgramCommand*>(command);
				Assert::IsNotNull(loadProgramCommand);
			}

			TEST_METHOD(WhenExecutedWithPowerOffRequested_PowerOffCommandReturned)
			{
				// arrange
				CommandFactoryTestingHelper commandFactoryHelper;
				CommandFactory* factory = commandFactoryHelper.GetCommandFactory();

				// act
				ICommand* command = factory->GetCommand(CommandType::POWEROFF);

				// assert
				PowerOffCommand* powerOffCommand = dynamic_cast<PowerOffCommand*>(command);
				Assert::IsNotNull(powerOffCommand);
			}

			TEST_METHOD(WhenExecutedWithPowerOnRequested_PowerOnCommandReturned)
			{
				// arrange
				CommandFactoryTestingHelper commandFactoryHelper;
				CommandFactory* factory = commandFactoryHelper.GetCommandFactory();

				// act
				ICommand* command = factory->GetCommand(CommandType::POWERON);

				// assert
				PowerOnCommand* powerOnCommand = dynamic_cast<PowerOnCommand*>(command);
				Assert::IsNotNull(powerOnCommand);
			}

			TEST_METHOD(WhenExecutedWithCheckPowerRequested_CheckPowerCommandReturned)
			{
				// arrange
				CommandFactoryTestingHelper commandFactoryHelper;
				CommandFactory* factory = commandFactoryHelper.GetCommandFactory();

				// act
				ICommand* command = factory->GetCommand(CommandType::CHECKPOWER);

				// assert
				CheckPowerCommand* checkPowerCommand = dynamic_cast<CheckPowerCommand*>(command);
				Assert::IsNotNull(checkPowerCommand);
			}

			TEST_METHOD(WhenExecutedWithGetAboutRequested_GetAboutCommandReturned)
			{
				// arrange
				CommandFactoryTestingHelper commandFactoryHelper;
				CommandFactory* factory = commandFactoryHelper.GetCommandFactory();

				// act
				ICommand* command = factory->GetCommand(CommandType::GETABOUT);

				// assert
				GetAboutCommand* getAboutCommand = dynamic_cast<GetAboutCommand*>(command);
				Assert::IsNotNull(getAboutCommand);
			}

			TEST_METHOD(WhenExecutedWithSetLedsRequested_SetLedsCommandReturned)
			{
				// arrange
				CommandFactoryTestingHelper commandFactoryHelper;
				CommandFactory* factory = commandFactoryHelper.GetCommandFactory();

				// act
				ICommand* command = factory->GetCommand(CommandType::SETLEDS);

				// assert
				SetLedsCommand* setLedsCommand = dynamic_cast<SetLedsCommand*>(command);
				Assert::IsNotNull(setLedsCommand);
			}

			TEST_METHOD(WhenExecutedWithNoneSupported_NullPtrReturned)
			{
				// arrange
				CommandFactoryTestingHelper commandFactoryHelper;
				CommandFactory* factory = commandFactoryHelper.GetCommandFactory();

				// act
				ICommand* command = factory->GetCommand(CommandType::NONE);

				// assert
				Assert::IsNull(command);
			}
		};
	}
}