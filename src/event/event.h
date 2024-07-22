#pragma once

namespace bds_btb {
    class Event {
    public:
        Event(const Event &) = delete;
        Event &operator=(const Event &) = delete;

        virtual ~Event() = default;

        [[nodiscard]] virtual std::string getEventName() const = 0;
        [[nodiscard]] virtual bool isCancellable() const = 0;
        [[nodiscard]] bool isCancelled() const {
            if (!isCancellable()) {
                return false;
            }
            return mCancelled;
        };
        void setCancelled(bool cancel)
        {
            if (isCancellable()) {
                mCancelled = cancel;
            }
        }
    private:
        bool mCancelled{false};
    };
};