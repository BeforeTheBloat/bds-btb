#include "protocol.h"

std::string ToHexString(const unsigned char* data, size_t length) {
	std::ostringstream oss;
	oss << std::hex << std::setfill('0');
	for (size_t i = 0; i < length; ++i) {
		oss << std::setw(2) << static_cast<int>(data[i]);
	}
	return oss.str();
}

void ProtocolManager::Init(RakPeerInterface* peer) {
	Packet* packet;
	while ((packet = peer->Receive())) {
		int packetType = packet->data[0];

		Logger::Info("Received packet with ID: " + std::to_string(packetType));

		ProtocolManager::PingPacketCallback(peer, packet);

		peer->DeallocatePacket(packet);
	}
};

void ProtocolManager::PingPacketCallback(RakPeerInterface* peer, Packet* packet) {
	std::string hexData = ToHexString(packet->data, packet->length);
	Logger::Info("packet data: " + hexData);
}; 