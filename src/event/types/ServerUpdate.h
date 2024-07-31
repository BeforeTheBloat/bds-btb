#pragma once

#include "../event.h"

class ServerUpdate : public Event {
public:
    ServerUpdate() {};

    int testingnumber = 0;

    EventType getType() const override {
        return EventType::ServerUpdateType;
    }
};
