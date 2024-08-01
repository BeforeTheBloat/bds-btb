#pragma once

#include "../pch.h"

class Logger {
public:
    enum Level {
        LOG_INFO,
        LOG_ERROR,
    };

    static void Log(Level level, const std::string& message);
    static void LuaLog(Level level, const std::string& message);

    static void Info(const std::string& message) {
        Log(LOG_INFO, message);
    }

    static void Error(const std::string& message) {
        Log(LOG_ERROR, message);
    }

    static void LuaInfo(const std::string& message) {
        LuaLog(LOG_INFO, message);
    }

    static void LuaError(const std::string& message) {
        LuaLog(LOG_ERROR, message);
    }

private:
    static std::string CurrentTime();
};