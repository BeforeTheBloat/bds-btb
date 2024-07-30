#include "pch.h"

int main() {
    std::string input;

    while (true) {
        bds_btb::EventManager eventManager;

        auto serverTickEvent = std::make_shared<bds_btb::ServerTick>();
        eventManager.addEvent(serverTickEvent);

        std::cout << "Hello World!" << std::endl;
        std::cout << "Enter something (or press Enter to exit): ";
        std::getline(std::cin, input);

        if (input.empty()) {
            break;
        }
        
        std::cout << "You entered: " << input << std::endl;
    }

    return 0;
}
