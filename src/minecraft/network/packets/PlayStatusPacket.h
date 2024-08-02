#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <base64.h>

using json = nlohmann::json;

class PlayStatusPacket {
public:
    int status;

    int LOGIN_SUCCESS = 0;
    int LOGIN_FAILED_CLIENT = 1;
    int LOGIN_FAILED_SERVER = 2;
    int PLAYER_SPAWN = 3;
    int LOGIN_FAILED_INVALID_TENANT = 4;
    int LOGIN_FAILED_VANILLA_EDU = 5;
    int LOGIN_FAILED_EDU_VANILLA = 6;
};