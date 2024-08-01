#include "logger.h"

void Logger::SetColor(Level level) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole == INVALID_HANDLE_VALUE) return;

        switch (level) {
        case LOG_SUCCESS:
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case LOG_ERROR:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        }
    #else
        if (isatty(fileno(stdout))) {
            switch (level) {
            case LOG_SUCCESS:
                std::cout << "\033[32m";
                break;
            case LOG_ERROR:
                std::cout << "\033[31m";
                break;
            }
        }
    #endif
}

void Logger::ResetColor() {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
#else
    if (isatty(fileno(stdout))) {
        std::cout << "\033[0m";
    }
#endif
}
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

    SetColor(level);

    switch (level) {
    case LOG_INFO:
        levelStr = "INFO";
        break;
    case LOG_SUCCESS:
        levelStr = "SUCCESS";
        break;
    case LOG_ERROR:
        levelStr = "ERROR";
        break;
    }
    
    std::cout << "[" << CurrentTime() << " " << levelStr << "] " << message << std::endl;

    ResetColor();
}

void Logger::LuaLog(Level level, const std::string& message) {
    std::string levelStr;

    SetColor(level);
    switch (level) {
    case LOG_INFO:
        levelStr = "INFO";
        break;
    case LOG_SUCCESS:
        levelStr = "SUCCESS";
        break;
    case LOG_ERROR:
        levelStr = "ERROR";
        break;
    }

    std::cout << "[" << CurrentTime() << " " << levelStr << "] [LUA] " << message << std::endl;

    ResetColor();
}
