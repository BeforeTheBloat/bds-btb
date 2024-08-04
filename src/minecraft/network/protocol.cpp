#include "protocol.h"

void ProtocolManager::Init(RakPeerInterface* peer) {
	Packet* packet;
	while ((packet = peer->Receive())) {
		int packetType = packet->data[0];

		Logger::Info("Received packet with ID: " + std::to_string(packetType));

		switch (packetType) {
		case 0:
			ProtocolManager::PingPacketCallback(peer, packet);
		case 1:
			ProtocolManager::PingPacketCallback(peer, packet);
		}

		peer->DeallocatePacket(packet);
	}
};

void ProtocolManager::PingPacketCallback(RakPeerInterface* peer, Packet* packet) {
	PingPacket* pingPacket = reinterpret_cast<PingPacket*>(packet);

	PingPacket pongPacket;
	pongPacket.packetType = 1;
	pongPacket.clientTimestamp = pingPacket->clientTimestamp;

	peer->Send(reinterpret_cast<const char*>(&pongPacket), sizeof(PingPacket), HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
	Logger::Info("send a pong");
};