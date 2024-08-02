#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <base64.h>

using json = nlohmann::json;

class LoginPacket {
public:
    static const uint8_t NETWORK_ID = 1;

    std::string username;
    int protocol;
    uint8_t gameEdition;
    std::string clientUUID;
    long long clientId;
};