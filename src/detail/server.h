#pragma once

namespace bds_btb::detail {
    class IServer {
        IServer() = default;
        IServer(const IServer&) = delete;
        IServer &operator=(const IServer&) = delete;
        virtual ~IServer() = default;

        [[nodiscard]] virtual std::string getName() const = 0;
        [[nodiscard]] virtual std::string getVersion() const = 0;
        [[nodiscard]] virtual std::string getMinecraftVersion() const = 0;
    };
};