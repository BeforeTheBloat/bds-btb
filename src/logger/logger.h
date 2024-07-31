#pragma once

#include "../pch.h"

class Logger {
public:
    enum Level {
        INFO,
        ERROR
    };

    static void Log(Level level, const std::string& message);

    static void Info(const std::string& message) {
        Log(INFO, message);
    }

    static void Error(const std::string& message) {
        Log(ERROR, message);
    }

private:
    static std::string CurrentTime();
};