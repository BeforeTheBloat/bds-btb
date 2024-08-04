#include "pch.h"
#include "event/types/ServerUpdate.h"

struct ResponsePacket1 {
    int64_t pingId;
    int64_t serverId;
    std::string identifier;
};

void onServerUpdate(void* event) {
    ServerUpdate* ev = static_cast<ServerUpdate*>(event);
    // Handle server update event
}

std::string to_hex_string(unsigned char byte) {
    const char* hexDigits = "0123456789ABCDEF";
    std::string hexStr;
    hexStr += hexDigits[byte >> 4];
    hexStr += hexDigits[byte & 0x0F];
    return hexStr;
}

int main() {
    try {
        Logger::Info("BDS-BTB Started...");

        Logger::Info("Attempting to open socket.");

        RakPeerInterface* peer = RakPeerInterface::GetInstance();
        SocketDescriptor sd(19132, 0);
        peer->Startup(1, &sd, 1);
        peer->SetMaximumIncomingConnections(10);

        Logger::Success("Socket opened (Port 19132).");

        LuaScripting::Init();

        while (true) {
            EventManager::registerListener(ServerUpdateType, onServerUpdate);

            ProtocolManager::Init(peer);
            

            ServerUpdate event;
            event.testingnumber = 1;
            EventManager::triggerEvent(&event);
        }

        LuaScripting::Close();
        peer->Shutdown(100);
        RakPeerInterface::DestroyInstance(peer);

        LuaScripting::Close();
    }
    catch (const std::exception& e) {
        Logger::Error(std::string("Exception: ") + e.what());
        return 1;
    }
    catch (...) {
        Logger::Error("Unknown exception occurred.");
        return 1;
    }

    return 0;
}
