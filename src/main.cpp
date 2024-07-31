#include "pch.h"

#include "event/types/ServerUpdate.h"

void onServerUpdate(void* event) {
    ServerUpdate* ev = static_cast<ServerUpdate*>(event);
    
}

int main() {
    Logger::Info("BDS-BTB Started...");
    while (true) {
        // game loop running in the server
        EventManager::registerListener(ServerUpdateType, onServerUpdate);

        ServerUpdate event;
        event.testingnumber = 1;
        EventManager::triggerEvent(&event);
    }

    return 0;
}
