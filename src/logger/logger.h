#pragma once

#include "../pch.h"

class Logger {
public:
    enum Level {
        LOG_INFO,
        LOG_ERROR,
    };

    static void Log(Level level, const std::string& message);

    static void Info(const std::string& message) {
        Log(LOG_INFO, message);
    }

    static void Error(const std::string& message) {
        Log(LOG_ERROR, message);
    }

private:
    static std::string CurrentTime();
};