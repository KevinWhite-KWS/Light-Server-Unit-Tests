#include "CppUnitTest.h"

#include "../../../Light-Server/src/Orchastrator/LightServerOrchastrator.h"
#include "../../../Light-Server/src/Orchastrator/Timer.h"
#include "../../../Light-Server/src/LPE/Executor/LpExecutor.h"
#include "../../../Light-Server/src/LPE/StateBuilder/LpState.h"
#include "../../../Light-Server/src/Renderer/PixelRenderer.h"
#include "../../../Light-Server/src/DomainInterfaces.h"
#include "../../../Light-Server/src/Commands/CommandFactory.h"

#include "../../ExternalDependencies/fakeit.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fakeit;

namespace LS {
	namespace Orchastrator {
		class LightServerOrchastratorTester : public LightServerOrchastrator {
		public:
			LightServerOrchastratorTester(Timer* timer, LpExecutor* lpExecutor, LpState* primaryLpState, PixelRenderer* renderer, ILightWebServer* webServer, CommandFactory* commandFactory)
				:LightServerOrchastrator(timer, lpExecutor, primaryLpState, renderer, webServer, commandFactory) {
			}

			LpiExecutorOutput* GetLpiExecutorOutput() {
				return &lpiExecutorOutput;
			}
		};


		TEST_CLASS(StopPrograms) {
		public:
			TEST_METHOD(WhenCalled_ClearsPrimaryLpState)
			{
				// arrange
				Mock<Timer> mockTimer;
				Mock<LpExecutor> mockExecutor;
				Mock<LpState> mockPrimaryState;
				When(Method(mockPrimaryState, reset)).Return();
				Mock<PixelRenderer> mockRenderer;
				Mock<ILightWebServer> mockWebServer;
				Mock<CommandFactory> mockCommandFactory;
				LightServerOrchastrator orchastrator = LightServerOrchastrator(&mockTimer.get(), &mockExecutor.get(), &mockPrimaryState.get(), &mockRenderer.get(), &mockWebServer.get(), &mockCommandFactory.get());

				// act
				orchastrator.StopPrograms();

				// assert
				Verify(Method(mockPrimaryState, reset));
			}
		};

		TEST_CLASS(Execute) {
		public:
			TEST_METHOD(WhenNotTime_FalseReturned)
			{
				// arrange
				Mock<Timer> mockTimer;
				When(Method(mockTimer, IsTime)).Return(false);
				Mock<LpExecutor> mockExecutor;
				Mock<LpState> mockPrimaryState;
				When(Method(mockPrimaryState, reset)).Return();
				Mock<PixelRenderer> mockRenderer;
				Mock<ILightWebServer> mockWebServer;
				Mock<CommandFactory> mockCommandFactory;
				LightServerOrchastrator orchastrator = LightServerOrchastrator(&mockTimer.get(), &mockExecutor.get(), &mockPrimaryState.get(), &mockRenderer.get(), &mockWebServer.get(), &mockCommandFactory.get());

				// act
				bool executed = orchastrator.Execute();

				// assert
				Assert::IsFalse(executed);
			}

			TEST_METHOD(WhenTimeButNotRunning_FalseReturned)
			{
				// arrange
				Mock<Timer> mockTimer;
				When(Method(mockTimer, IsTime)).Return(true);
				Mock<LpExecutor> mockExecutor;
				Mock<LpState> mockPrimaryState;
				When(Method(mockPrimaryState, reset)).Return();
				Mock<PixelRenderer> mockRenderer;
				Mock<ILightWebServer> mockWebServer;
				Mock<CommandFactory> mockCommandFactory;
				LightServerOrchastrator orchastrator = LightServerOrchastrator(&mockTimer.get(), &mockExecutor.get(), &mockPrimaryState.get(), &mockRenderer.get(), &mockWebServer.get(), &mockCommandFactory.get());
				orchastrator.Stop();

				// act
				bool executed = orchastrator.Execute();

				// assert
				Assert::IsFalse(executed);
			}

			TEST_METHOD(WhenTimeAndRunning_TrueReturned)
			{
				// arrange
				Mock<Timer> mockTimer;
				When(Method(mockTimer, IsTime)).Return(true);
				Mock<LpExecutor> mockExecutor;
				When(Method(mockExecutor, Execute)).Return();
				Mock<LpState> mockPrimaryState;
				When(Method(mockPrimaryState, reset)).Return();
				Mock<PixelRenderer> mockRenderer;
				Mock<ILightWebServer> mockWebServer;
				When(Method(mockWebServer, HandleNextCommand)).Return(CommandType::NONE);
				Mock<CommandFactory> mockCommandFactory;
				LightServerOrchastrator orchastrator = LightServerOrchastrator(&mockTimer.get(), &mockExecutor.get(), &mockPrimaryState.get(), &mockRenderer.get(), &mockWebServer.get(), &mockCommandFactory.get());

				// act
				bool executed = orchastrator.Execute();

				// assert
				Assert::IsTrue(executed);
			}

			TEST_METHOD(WhenTimeAndRunning_LpExecuted)
			{
				// arrange
				Mock<Timer> mockTimer;
				When(Method(mockTimer, IsTime)).Return(true);
				Mock<LpExecutor> mockExecutor;
				When(Method(mockExecutor, Execute)).Return();
				Mock<LpState> mockPrimaryState;
				When(Method(mockPrimaryState, reset)).Return();
				Mock<PixelRenderer> mockRenderer;
				Mock<ILightWebServer> mockWebServer;
				When(Method(mockWebServer, HandleNextCommand)).Return(CommandType::NONE);
				Mock<CommandFactory> mockCommandFactory;
				LightServerOrchastrator orchastrator = LightServerOrchastrator(&mockTimer.get(), &mockExecutor.get(), &mockPrimaryState.get(), &mockRenderer.get(), &mockWebServer.get(), &mockCommandFactory.get());

				// act
				bool executed = orchastrator.Execute();

				// assert
				Verify(Method(mockExecutor, Execute));
			}

			TEST_METHOD(WhenInstructionsToRender_RendererCalled)
			{
				// arrange
				Mock<Timer> mockTimer;
				When(Method(mockTimer, IsTime)).Return(true);
				Mock<LpExecutor> mockExecutor;
				When(Method(mockExecutor, Execute)).Return();
				Mock<LpState> mockPrimaryState;
				When(Method(mockPrimaryState, reset)).Return();
				Mock<PixelRenderer> mockRenderer;
				When(Method(mockRenderer, SetPixels)).Return();
				When(Method(mockRenderer, ShowPixels)).Return();
				Mock<ILightWebServer> mockWebServer;
				When(Method(mockWebServer, HandleNextCommand)).Return(CommandType::NONE);
				Mock<CommandFactory> mockCommandFactory;
				LightServerOrchastratorTester orchastrator = LightServerOrchastratorTester(&mockTimer.get(), &mockExecutor.get(), &mockPrimaryState.get(), &mockRenderer.get(), &mockWebServer.get(), &mockCommandFactory.get());
					// add something to the LP, anything will do, so we have something to be rendered
				orchastrator.GetLpiExecutorOutput()->SetNextRenderingInstruction(&Colour(255, 255, 255), 5);

				// act
				bool executed = orchastrator.Execute();

				// assert
				Verify(Method(mockRenderer, SetPixels));
				Verify(Method(mockRenderer, ShowPixels));
			}

			TEST_METHOD(WhenCommandWaiting_ExecuteCommand)
			{
				// arrange
				Mock<Timer> mockTimer;
				When(Method(mockTimer, IsTime)).Return(true);
				Mock<LpExecutor> mockExecutor;
				When(Method(mockExecutor, Execute)).Return();
				Mock<LpState> mockPrimaryState;
				When(Method(mockPrimaryState, reset)).Return();
				Mock<PixelRenderer> mockRenderer;
				Mock<ILightWebServer> mockWebServer;
				When(Method(mockWebServer, HandleNextCommand)).Return(CommandType::GETABOUT);
				Mock<GetAboutCommand> mockGetAboutCommand;
				When(Method(mockGetAboutCommand, ExecuteCommand)).Return(true);
				Mock<CommandFactory> mockCommandFactory;
				When(Method(mockCommandFactory, GetCommand)).Return(&mockGetAboutCommand.get());
				LightServerOrchastratorTester orchastrator = LightServerOrchastratorTester(&mockTimer.get(), &mockExecutor.get(), &mockPrimaryState.get(), &mockRenderer.get(), &mockWebServer.get(), &mockCommandFactory.get());
				// add something to the LP, anything will do, so we have something to be rendered

				// act
				bool executed = orchastrator.Execute();

				// assert
				Verify(Method(mockGetAboutCommand, ExecuteCommand));
			}
		};
	}
}