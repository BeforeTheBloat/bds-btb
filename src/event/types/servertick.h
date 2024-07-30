#include "../../pch.h"

namespace bds_btb {

    class ServerTick : public Event {
    public:
        ServerTick() {}

        [[nodiscard]] std::string getEventName() const override {
            return "ServerTick";
        }

        [[nodiscard]] bool isCancellable() const override {
            return false; // ServerTick events are not cancellable
        }
    };

};