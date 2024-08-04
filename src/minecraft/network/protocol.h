#pragma once

#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>

#include "packets/PingPacket.h"

using namespace RakNet;

class ProtocolManager {
public:
	static void Init(RakPeerInterface* peer);
	static void PingPacketCallback(RakPeerInterface* peer, Packet* packet);
};