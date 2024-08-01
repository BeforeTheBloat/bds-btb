#include "logger.h"

std::string Logger::CurrentTime() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::ostringstream oss;
    oss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");

    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;
    oss << ":" << std::setw(3) << std::setfill('0') << milliseconds.count();

    return oss.str();
}

void Logger::Log(Level level, const std::string& message) {
    std::string levelStr;
    switch (level) {
    case LOG_INFO:
        levelStr = "INFO";
        break;
    case LOG_ERROR:
        levelStr = "ERROR";
        break;
    }
    
    std::cout << "[" << CurrentTime() << " " << levelStr << "] " << message << std::endl;
}

void Logger::LuaLog(Level level, const std::string& message) {
    std::string levelStr;
    switch (level) {
    case LOG_INFO:
        levelStr = "INFO";
        break;
    case LOG_ERROR:
        levelStr = "ERROR";
        break;
    }

    std::cout << "[" << CurrentTime() << " " << levelStr << "] [LUA] " << message << std::endl;
}
