#ifndef _MOCK_WEBSERVER_h_
#define _MOCK_WEBSERVER_h_

#include <stdint.h>
#include "..\..\Light Server\src\DomainInterfaces.h"

namespace LS {
	class Mock_LightWebServer : public LightWebServer {
		public :
			Mock_LightWebServer(IWebServer* webServer, FixedSizeCharBuffer* loadingBuffer) 
				: LightWebServer(webServer, loadingBuffer) {

			}

			static void HandleCommandInvalid(ILightWebServer* lightWebServer, IWebServer& server, IWebServer::ConnectionType type, char* head, bool tailComplete) {
				LightWebServer::HandleCommandInvalid(lightWebServer, server, type, head, tailComplete);
			}

			static void HandleCommandPowerOff(ILightWebServer* lightWebServer, IWebServer& server, IWebServer::ConnectionType type, char* head, bool tailComplete) {
				LightWebServer::HandleCommandPowerOff(lightWebServer, server, type, head, tailComplete);
			}

			static void HandleCommandLoadProgram(ILightWebServer* lightWebServer, IWebServer& server, IWebServer::ConnectionType type, char* head, bool tailComplete) {
				LightWebServer::HandleCommandLoadProgram(lightWebServer, server, type, head, tailComplete);
			}

			static void HandleCommandPowerOn(ILightWebServer* lightWebServer, IWebServer& server, IWebServer::ConnectionType type, char* head, bool tailComplete) {
				LightWebServer::HandleCommandPowerOn(lightWebServer, server, type, head, tailComplete);
			}

			static void HandleCheckPower(ILightWebServer* lightWebServer, IWebServer& server, IWebServer::ConnectionType type, char* head, bool tailComplete) {
				LightWebServer::HandleCommandCheckPower(lightWebServer, server, type, head, tailComplete);
			}

			static void HandleGetAbout(ILightWebServer* lightWebServer, IWebServer& server, IWebServer::ConnectionType type, char* head, bool tailComplete) {
				LightWebServer::HandleCommandGetAbout(lightWebServer, server, type, head, tailComplete);
			}
	};


	class Mock_WebServer : public IWebServer {
		public:
			ILightWebServer* lws = nullptr;

			char* serverReadBuffer = nullptr;
			int serverReadBufferPos = 0;

			bool beginCalled = false;
			bool httpSuccessCalled = false;
			bool httpFailCalled = false;
			bool httpNoContentCalled = false;
			bool connectionClosedCalled = false;

			bool doInvalidCommand = false;
			bool doLoadProgramCommand = false;
			bool doPowerOffCommand = false;
			bool doPowerOnCommand = false;
			bool doCheckPowerCommand = false;
			bool doGetAbout = false;

			Mock_WebServer() {
			}

			void begin() {
				beginCalled = true;
			}

			void setDefaultCommand(Command* cmd) {
			}

			void setFailureCommand(Command* cmd) {
			}

			void httpFail() {
				httpFailCalled = true;
			}

			void httpSuccess(const char* contentType = "text/html; charset=utf-8",
				const char* extraHeaders = NULL) {
				httpSuccessCalled = true;
			}

			void httpNoContent() {
				httpNoContentCalled = true;
			}

			int read() {
				if (serverReadBuffer == nullptr || *serverReadBuffer == 0)
					return -1;

				return *serverReadBuffer++;
			}
			void flushBuf() {
			}
			void addCommand(const char* verb, Command* cmd) {
			}
			void processConnection(char* buff, int* bufflen) {
				if (doInvalidCommand) {
					Mock_LightWebServer::HandleCommandInvalid(lws, *this, ConnectionType::GET, nullptr, false);
				}
				else if (doPowerOffCommand) {
					Mock_LightWebServer::HandleCommandPowerOff(lws, *this, ConnectionType::GET, nullptr, false);
				}
				else if (doLoadProgramCommand) {
					Mock_LightWebServer::HandleCommandLoadProgram(lws, *this, ConnectionType::GET, nullptr, false);
				}
				else if (doPowerOnCommand) {
					Mock_LightWebServer::HandleCommandPowerOn(lws, *this, ConnectionType::GET, nullptr, false);
				}
				else if (doCheckPowerCommand) {
					Mock_LightWebServer::HandleCheckPower(lws, *this, ConnectionType::GET, nullptr, false);
				}
				else if (doGetAbout) {
					Mock_LightWebServer::HandleGetAbout(lws, *this, ConnectionType::GET, nullptr, false);
				}
			}
			void setLightWebServer(ILightWebServer* lightWebServer) {
				lws = lightWebServer;
			}
			void closeConnection() {
				connectionClosedCalled = true;
			}

			void printP(const char* str) {

			}
	};
}
#endif
