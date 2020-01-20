#include "CppUnitTest.h"
#include <iostream>

#include "../../Light Server/src/LightWebServer.h"
#include "../mocks/Mock_WebServer.h"
#include "../../Light Server/src/DomainInterfaces.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using LS::LightWebServer;

namespace LS
{
	namespace LightWebServ {
		TEST_CLASS(Start) {
			public:
				TEST_METHOD(Start_BeginInvoked)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					lws.Start();

					// assert
					Assert::IsTrue(mockws.beginCalled);
				}
		};

		TEST_CLASS(GetLoadingBuffer) {
			public:
				TEST_METHOD(GetLoadingBuffer_Clear_BufferCleared)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");
					char* pBuf = loadingBuffer.GetBuffer();
					*pBuf++ = 'K';
					*pBuf = 0;

					// act
					pBuf = lws.GetLoadingBuffer(true);

					// assert
					Assert::AreEqual((char)0, *pBuf);
				}

				TEST_METHOD(GetLoadingBuffer_NotClear_BufferNotCleared)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");
					char* pBuf = loadingBuffer.GetBuffer();
					*pBuf++ = 'K';
					*pBuf = 0;

					// act
					pBuf = lws.GetLoadingBuffer(false);

					// assert
					Assert::AreEqual('K', *pBuf);
				}
		};

		TEST_CLASS(SetCommandType) {
			public:
				TEST_METHOD(SetCommandType_LoadProgram_CommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");
					lws.SetCommandType(CommandType::LOADPROGRAM);

					// act
					CommandType command = lws.GetCommandType();

					// assert
					Assert::AreEqual((int)CommandType::LOADPROGRAM, (int)command);
				}
		};

		TEST_CLASS(HandleNextCommand) {
			public:
				TEST_METHOD(HandleNextCommand_NoCommandReceived_NoneCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::NONE, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_InvalidCommandReceived_InvalidCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.doInvalidCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					// LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer);

					// act
 					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::INVALID, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_PowerOffCommandReceived_PowerOffCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = " ";
					mockws.doPowerOffCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::POWEROFF, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_PowerOffCommandReceived_NoAuth_NoAuthSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = "expected";
					mockws.doPowerOffCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, "actual");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::NOAUTH, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_LoadProgramCommandReceived_LoadProgramCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = " ";
					mockws.doLoadProgramCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::LOADPROGRAM, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_LoadProgramCommandReceived_NoAuth_NoAuthSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = "expected";
					mockws.doLoadProgramCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, "actual");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::NOAUTH, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_LoadProgramCommandReceived_BufferContainsExpected)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = " ";
					mockws.doLoadProgramCommand = true;
					mockws.serverReadBuffer = "{testing}";
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");
					// loadingBuffer.LoadFromBuffer("{testing}");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					int areEqual = strcmp("{testing}", loadingBuffer.GetBuffer());
					Assert::AreEqual(0, areEqual);
				}

				TEST_METHOD(HandleNextCommand_PowerOn_PowerOnCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = " ";
					mockws.doPowerOnCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::POWERON, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_PowerOn_NoAuth_NoAuthSent)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = "expected";
					mockws.doPowerOnCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, "actual");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::NOAUTH, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_PowerOn_BufferContainsExpected)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = " ";
					mockws.doPowerOnCommand = true;
					mockws.serverReadBuffer = "FF0000";
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");
					// loadingBuffer.LoadFromBuffer("{testing}");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					int areEqual = strcmp("FF0000", loadingBuffer.GetBuffer());
					Assert::AreEqual(0, areEqual);
				}

				TEST_METHOD(HandleNextCommand_CheckPowerCommandReceived_CheckPowerCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.doCheckPowerCommand = true;
					mockws.usernamePassword = " ";
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::CHECKPOWER, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_CheckPowerCommandReceived_NotAuthed_NotAuthedSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.doCheckPowerCommand = true;
					mockws.usernamePassword = "expected";
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, "actual");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::NOAUTH, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_GetAboutCommandReceived_GetAboutCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = " ";
					mockws.doGetAbout = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::GETABOUT, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_GetAboutCommandReceived_NotAuthed_NotAuthedSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = "expected";
					mockws.doGetAbout = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, "actual");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::NOAUTH, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_SetLedsCommandReceived_SetLedsCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = " ";
					mockws.doSetLeds = true;
					mockws.connType = IWebServer::ConnectionType::POST;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::SETLEDS, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_SetLedsCommandReceived_NotAuthed_NotAuthedSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = "expected";
					mockws.doSetLeds = true;
					mockws.connType = IWebServer::ConnectionType::POST;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, "actual");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::NOAUTH, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_SetLedsCommandReceived_NotPost_InvalidCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = " ";
					mockws.doSetLeds = true;
					mockws.connType = IWebServer::ConnectionType::GET;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::INVALID, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_SetLedsCommandReceived_BufferContainsExpected)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.usernamePassword = " ";
					mockws.doSetLeds = true;
					mockws.connType = IWebServer::ConnectionType::POST;
					mockws.serverReadBuffer = "{testing}";
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					int areEqual = strcmp("{testing}", loadingBuffer.GetBuffer());
					Assert::AreEqual(0, areEqual);
				}
		};

		TEST_CLASS(RespondOK) {
			public:
				TEST_METHOD(RespondOK_HttpSuccessSent)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					lws.RespondOK();

					// assert
					Assert::IsTrue(mockws.httpSuccessCalled);
				}

				TEST_METHOD(RespondOK_ConnectionClosed)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

					// act
					lws.RespondOK();

					// assert
					Assert::IsTrue(mockws.connectionClosedCalled);
				}
		};

		TEST_CLASS(RespondNoContent) {
		public:
			TEST_METHOD(RespondNoContent_HttpNoContentSent)
			{
				// arrange
				Mock_WebServer mockws = Mock_WebServer();
				FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
				LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

				// act
				lws.RespondNoContent();

				// assert
				Assert::IsTrue(mockws.httpNoContentCalled);
			}

			TEST_METHOD(RespondOK_ConnectionClosed)
			{
				// arrange
				Mock_WebServer mockws = Mock_WebServer();
				FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
				LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

				// act
				lws.RespondNoContent();

				// assert
				Assert::IsTrue(mockws.connectionClosedCalled);
			}
		};

		TEST_CLASS(RespondError) {
		public:
			TEST_METHOD(RespondError_HttpErrorSent)
			{
				// arrange
				Mock_WebServer mockws = Mock_WebServer();
				FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
				LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

				// act
				lws.RespondError();

				// assert
				Assert::IsTrue(mockws.httpFailCalled);
			}

			TEST_METHOD(RespondError_ConnectionClosed)
			{
				// arrange
				Mock_WebServer mockws = Mock_WebServer();
				FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
				LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

				// act
				lws.RespondError();

				// assert
				Assert::IsTrue(mockws.connectionClosedCalled);
			}
		};

		TEST_CLASS(RespondNotAuthorised) {
		public:
			TEST_METHOD(RespondNotAuthorised_HttpNotAuthorisedSent)
			{
				// arrange
				Mock_WebServer mockws = Mock_WebServer();
				FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
				LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

				// act
				lws.RespondNotAuthorised();

				// assert
				Assert::IsTrue(mockws.httpUnauthorizedCalled);
			}

			TEST_METHOD(RespondNotAuthorised_ConnectionClosed)
			{
				// arrange
				Mock_WebServer mockws = Mock_WebServer();
				FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
				LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer, " ");

				// act
				lws.RespondNotAuthorised();

				// assert
				Assert::IsTrue(mockws.connectionClosedCalled);
			}
		};

		TEST_CLASS(CheckAuth) {
		public:
			TEST_METHOD(CheckAuth_IncorrectAuth_FalseReturned)
			{
				// arrange
				Mock_WebServer mockws = Mock_WebServer();
				mockws.usernamePassword = "IncorrectUsernamePassword";
				FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
				Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, "Base64UsernamePassword");

				// act
				bool isAuthorised = lws.CheckAuth(&lws, mockws);

				// assert
				Assert::IsFalse(isAuthorised);
			}

			TEST_METHOD(CheckAuth_CorrectAuth_TrueReturned)
			{
				// arrange
				Mock_WebServer mockws = Mock_WebServer();
				mockws.usernamePassword = "Base64UsernamePassword";
				FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
				Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, "Base64UsernamePassword");

				// act
				bool isAuthorised = lws.CheckAuth(&lws, mockws);

				// assert
				Assert::IsTrue(isAuthorised);
			}

			TEST_METHOD(CheckAuth_IncorrectAuth_NoAuthExpected)
			{
				// arrange
				Mock_WebServer mockws = Mock_WebServer();
				mockws.usernamePassword = "IncorrectUsernamePassword";
				FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
				Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer, "Base64UsernamePassword");

				// act
				lws.CheckAuth(&lws, mockws);

				// assert
				LS::CommandType cmdType = lws.GetCommandType();
				Assert::AreEqual((int)LS::CommandType::NOAUTH, (int)cmdType);
			}
		};
	}
}