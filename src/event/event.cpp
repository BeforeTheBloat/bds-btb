#include "event.h"

std::unordered_map<EventType, std::vector<EventManager::EventListener>> EventManager::listeners;

void EventManager::registerListener(EventType eventType, EventListener listener) {
    listeners[eventType].push_back(listener);
}

void EventManager::triggerEvent(Event* event) {
    EventType type = event->getType();
    if (listeners.find(type) != listeners.end()) {
        for (auto& listener : listeners[type]) {
            listener(static_cast<void*>(event));
        }
    }
}
