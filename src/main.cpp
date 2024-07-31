#include "pch.h"

#include "event/types/ServerUpdate.h"

void onServerUpdate(void* event) {
    ServerUpdate* ev = static_cast<ServerUpdate*>(event);
    std::cout << ev->testingnumber << std::endl;
}

int main() {
    while (true) {
        EventManager::registerListener(ServerUpdateType, onServerUpdate);

        ServerUpdate event;
        event.testingnumber = 1;
        EventManager::triggerEvent(&event);
    }

    return 0;
}
