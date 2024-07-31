#pragma once

#include "../pch.h"
#include <functional>
#include <vector>
#include <unordered_map>

enum EventType {
    ServerUpdateType,
};

class Event {
public:
    virtual EventType getType() const = 0;
    bool* mCancelled;
};


class EventManager {
public:
    using EventListener = void(*)(void*);

    static void registerListener(EventType eventType, EventListener listener);
    static void triggerEvent(Event* event);

private:
    static std::unordered_map<EventType, std::vector<EventListener>> listeners;
};
