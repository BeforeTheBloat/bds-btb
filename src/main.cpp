#include "pch.h"
#include "event/types/ServerUpdate.h"

void onServerUpdate(void* event) {
    ServerUpdate* ev = static_cast<ServerUpdate*>(event);
    // Handle server update event
}

int main() {
    try {
        Logger::Info("BDS-BTB Started...");

        Logger::Info("Attempting to open socket.");

        SocketAbstraction server;
        if (!server.openSocket("0.0.0.0", 19132)) {
            throw std::runtime_error("Failed to open server socket");
        }

        Logger::Info("Socket opened (Port 19132).");

        const size_t bufferSize = 1024;
        std::vector<char> buffer(bufferSize);

        LuaScripting::Init();

        while (true) {
            EventManager::registerListener(ServerUpdateType, onServerUpdate);

            std::string receivedMessage = server.receiveData(bufferSize);
            if (!receivedMessage.empty()) {
                Logger::Info("Received message: " + receivedMessage);
            }

            ServerUpdate event;
            event.testingnumber = 1;
            EventManager::triggerEvent(&event);
        }

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
