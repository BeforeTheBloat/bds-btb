#pragma once

#include <vector>
#include <memory>

namespace bds_btb {

    class Event;

    class EventManager {
    public:
        EventManager() = default;
        EventManager(const EventManager &) = delete;
        EventManager &operator=(const EventManager &) = delete;
        virtual ~EventManager() = default;

        void addEvent(std::shared_ptr<Event> event) {
            mEvents.push_back(event);
        }

        void removeEvent(const std::shared_ptr<Event>& event) {
            auto it = std::remove(mEvents.begin(), mEvents.end(), event);
            mEvents.erase(it, mEvents.end());
        }

        [[nodiscard]] std::vector<std::shared_ptr<Event>> getEvents() const {
            return mEvents;
        }

        [[nodiscard]] std::shared_ptr<Event> getEventByName(const std::string &name) const {
            for (const auto &event : mEvents) {
                if (event->getEventName() == name) {
                    return event;
                }
            }
            return nullptr;
        }

    private:
        std::vector<std::shared_ptr<Event>> mEvents;
    };

};
