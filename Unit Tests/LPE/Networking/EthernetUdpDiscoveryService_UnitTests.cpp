#include "CppUnitTest.h"

#include "../../../../Light-Server/src/Networking/EthernetUdpDiscoveryService.h"
#include "../../../../Light-Server/src/Networking/IUdpService.h"

#include "../../../ExternalDependencies/fakeit.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace fakeit;


namespace LS {
	namespace Networking {
		namespace Udp {
			class TestEthernetUdpDiscoverService : public EthernetUdpDiscoveryService {
			public:
				TestEthernetUdpDiscoverService(uint16_t port, const char* replyMsg, const char* handshakeMsg, IUdpService* udp)
					: EthernetUdpDiscoveryService(port, replyMsg, handshakeMsg, udp) {
				}

				void SetPacketBuffer(char* newPacketBuffer) {
					strcpy(packetBuffer, newPacketBuffer);
				}

				char* GetPacketBuffer() {
					return packetBuffer;
				}
			};


			TEST_CLASS(StartDiscoveryService) {
				public:
					TEST_METHOD(WhenCalled_StartsListernetOnSpecifiedPort)
					{
						// arrange
						Mock<IUdpService> mockUdpService;
						When(Method(mockUdpService, begin)).Return();
						const uint16_t port = 8888;
						const char* replyMsg = "Hello world";
						const char* handshakeMsg = "HOLA";
						EthernetUdpDiscoveryService discoveryService(port, replyMsg, handshakeMsg, &mockUdpService.get());

						// act
						discoveryService.StartDiscoveryService();

						// assert
						Verify(Method(mockUdpService, begin).Using(port));
					}
			};

			TEST_CLASS(CheckForHandshake) {
				public:
					TEST_METHOD(WhenCalled_NoPacketReceived_ReadNotCalled)
					{
						// arrange
						Mock<IUdpService> mockUdpService;
						When(Method(mockUdpService, parsePacket)).Return(0);
						When(Method(mockUdpService, read)).Return();
						const uint16_t port = 8888;
						const char* replyMsg = "Hello world";
						const char* handshakeMsg = "HOLA";
						EthernetUdpDiscoveryService discoveryService(port, replyMsg, handshakeMsg, &mockUdpService.get());

						// act
						discoveryService.CheckForHandshake();

						// assert
						Verify(Method(mockUdpService, read)).Never();
					}

					TEST_METHOD(WhenCalled_PacketReceivedButNotHandshake_ReadNotCalled)
					{
						// arrange
						Mock<IUdpService> mockUdpService;
						When(Method(mockUdpService, parsePacket)).Return(1);
						When(Method(mockUdpService, read)).Return();
						When(Method(mockUdpService, beginPacket)).Return();
						When(Method(mockUdpService, remoteIP)).Return();
						When(Method(mockUdpService, remotePort)).Return();
						const uint16_t port = 8888;
						const char* replyMsg = "Hello world";
						const char* handshakeMsg = "HOLA";
						TestEthernetUdpDiscoverService discoveryService(port, replyMsg, handshakeMsg, &mockUdpService.get());
						discoveryService.SetPacketBuffer("NOT HANDSHAKE");

						// act
						discoveryService.CheckForHandshake();

						// assert
						Verify(Method(mockUdpService, read)).Once();
						Verify(Method(mockUdpService, beginPacket)).Never();
					}

					TEST_METHOD(WhenCalled_PacketReceivedIsHandshake_CorrectReplySent)
					{
						// arrange
						Mock<IUdpService> mockUdpService;
						When(Method(mockUdpService, parsePacket)).Return(1);
						When(Method(mockUdpService, read)).Return();
						When(Method(mockUdpService, beginPacket)).Return();
						When(Method(mockUdpService, remoteIP)).Return();
						When(Method(mockUdpService, remotePort)).Return();
						When(Method(mockUdpService, write)).Return();
						When(Method(mockUdpService, endPacket)).Return();
						const uint16_t port = 8888;
						const char* replyMsg = "Hello world";
						char* handshakeMsg = "HOLA";
						TestEthernetUdpDiscoverService discoveryService(port, replyMsg, handshakeMsg, &mockUdpService.get());
						discoveryService.SetPacketBuffer(handshakeMsg);

						// act
						discoveryService.CheckForHandshake();

						// assert
						Verify(Method(mockUdpService, beginPacket)).Once();
						Verify(Method(mockUdpService, write).Using(replyMsg)).Once();
						Verify(Method(mockUdpService, endPacket)).Once();
					}

					TEST_METHOD(WhenCalled_PacketReceivedIsHandshake_PacketBufferIsCleared)
					{
						// arrange
						Mock<IUdpService> mockUdpService;
						When(Method(mockUdpService, parsePacket)).Return(1);
						When(Method(mockUdpService, read)).Return();
						When(Method(mockUdpService, beginPacket)).Return();
						When(Method(mockUdpService, remoteIP)).Return();
						When(Method(mockUdpService, remotePort)).Return();
						When(Method(mockUdpService, write)).Return();
						When(Method(mockUdpService, endPacket)).Return();
						const uint16_t port = 8888;
						const char* replyMsg = "Hello world";
						char* handshakeMsg = "HOLA";
						TestEthernetUdpDiscoverService discoveryService(port, replyMsg, handshakeMsg, &mockUdpService.get());
						discoveryService.SetPacketBuffer(handshakeMsg);

						// act
						discoveryService.CheckForHandshake();

						// assert
						Assert::IsTrue(discoveryService.GetPacketBuffer()[0] == 0x00);
					}
			};
		}
	}
}