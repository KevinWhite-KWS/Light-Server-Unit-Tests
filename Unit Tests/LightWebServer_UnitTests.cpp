#include "CppUnitTest.h"
#include <iostream>

#include "../../Light Server/src/LightWebServer.h"
#include "../mocks/Mock_WebServer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

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
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);

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
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);
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
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);
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
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);
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
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);

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
					mockws.doPowerOffCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer);

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::POWEROFF, (int)cmdType);
				}
				TEST_METHOD(HandleNextCommand_LoadProgramCommandReceived_LoadProgramCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.doLoadProgramCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer);

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::LOADPROGRAM, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_LoadProgramCommandReceived_BufferContainsExpected)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.doLoadProgramCommand = true;
					mockws.serverReadBuffer = "{testing}";
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer);
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
					mockws.doPowerOnCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer);

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::POWERON, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_PowerOn_BufferContainsExpected)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.doPowerOnCommand = true;
					mockws.serverReadBuffer = "FF0000";
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer);
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
					mockws.doInvalidCommand = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					// LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer);

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::INVALID, (int)cmdType);
				}

				TEST_METHOD(HandleNextCommand_GetAboutCommandReceived_GetAboutCommandSet)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					mockws.doGetAbout = true;
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					Mock_LightWebServer lws = Mock_LightWebServer((IWebServer*)&mockws, &loadingBuffer);

					// act
					CommandType cmdType = lws.HandleNextCommand();

					// assert
					Assert::AreEqual((int)CommandType::GETABOUT, (int)cmdType);
				}
		};

		TEST_CLASS(RespondOK) {
			public:
				TEST_METHOD(RespondOK_HttpSuccessSent)
				{
					// arrange
					Mock_WebServer mockws = Mock_WebServer();
					FixedSizeCharBuffer loadingBuffer = FixedSizeCharBuffer(10000);
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);

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
					LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);

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
				LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);

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
				LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);

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
				LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);

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
				LightWebServer lws = LightWebServer((IWebServer*)&mockws, &loadingBuffer);

				// act
				lws.RespondError();

				// assert
				Assert::IsTrue(mockws.connectionClosedCalled);
			}
		};
	}
}