#include "pch.h"

#include "event/types/ServerUpdate.h"

void onServerUpdate(void* event) {
    ServerUpdate* ev = static_cast<ServerUpdate*>(event);
    
}

int main() {
    Logger::Info("BDS-BTB Started...");
    Logger::Info("Attemping to open socket.");

    SocketAbstraction server;
    if (!server.openSocket("0.0.0.0", 19132)) {
        Logger::Error("Failed to open server socket");
        return 1;
    }

    Logger::Info("Socket opened (Port 19132).");

    while (true) {
        // game loop running in the server
        EventManager::registerListener(ServerUpdateType, onServerUpdate);

        ServerUpdate event;
        event.testingnumber = 1;
        EventManager::triggerEvent(&event);
    }

    // clean up resources and exit
    server.closeSocket();


    return 0;
}
