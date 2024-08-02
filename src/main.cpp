#include "pch.h"
#include "event/types/ServerUpdate.h"

using namespace RakNet;

void onServerUpdate(void* event) {
    ServerUpdate* ev = static_cast<ServerUpdate*>(event);
    // Handle server update event
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

                switch (packet->data[0]) {
                case 1:
                    LoginPacket* loginPacket = (LoginPacket*)packet;
                    
                    Logger::Info(("Protocol: " + std::to_string(loginPacket->protocol)));
                    Logger::Info(("Game Edition: " + std::to_string(loginPacket->gameEdition)));


                };

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
