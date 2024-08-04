#pragma once

#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <MessageIdentifiers.h>
#include <BitStream.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <base64.h>

using json = nlohmann::json;
using namespace RakNet;

struct PingPacket : Packet {
    uint8_t packetType;
    int64_t clientTimestamp;
};