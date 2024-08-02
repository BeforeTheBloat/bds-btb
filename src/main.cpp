#include "pch.h"
#include "event/types/ServerUpdate.h"

using namespace RakNet;

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

            Packet* packet;
            while ((packet = peer->Receive())) {

                Logger::Info("Received packet with ID: " + std::to_string(packet->data[0]));

                std::string hexData;
                for (size_t i = 0; i < packet->length; ++i) {
                    hexData += " " + to_hex_string(packet->data[i]);
                }
                Logger::Info("Packet Data (Hex):" + hexData);

                std::string u8Data(reinterpret_cast<const char*>(packet->data), packet->length);
                Logger::Info("Packet Data (u8string): " + std::string(u8Data.begin(), u8Data.end()));

                std::string charData(reinterpret_cast<const char*>(packet->data), packet->length);
                Logger::Info("Packet Data (char): " + charData);

                if (packet->data[0] == 1) {
                    Logger::Info("Ping received, sending empty packet back.");

                    ResponsePacket1 responsePacket;
                    responsePacket.pingId = 0x00000000003c6d0d;
                    responsePacket.serverId = 0x00000000372cdc9e;
                    responsePacket.identifier = "MCPE;Steve;2 7;1.1.3;0;20";

                    BitStream bs;
                    bs.Write(reinterpret_cast<const char*>(&responsePacket), sizeof(responsePacket));
                    peer->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
                }

                peer->DeallocatePacket(packet);
            }
            

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
