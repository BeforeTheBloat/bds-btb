#include "scripting.h"

namespace fs = std::filesystem;

namespace LuaScripting {
    lua_State* L = nullptr;

    int lua_logger_info(lua_State* L) {
        const char* message = luaL_checkstring(L, 1);
        Logger::LuaInfo(message);
        return 0;
    }

    int lua_logger_error(lua_State* L) {
        const char* message = luaL_checkstring(L, 1);
        Logger::LuaError(message);
        return 0;
    }

    void Init() {
        L = luaL_newstate();
        luaL_openlibs(L);

        lua_register(L, "LoggerInfo", lua_logger_info);
        lua_register(L, "LoggerError", lua_logger_error);

        std::string scriptDir = "scripts";
        for (const auto& entry : fs::directory_iterator(scriptDir)) {
            if (entry.path().extension() == ".lua") {
                Logger::Info("Loaded script: " + entry.path().string());
                if (luaL_dofile(L, entry.path().string().c_str())) {
                    Logger::Error("Failed to run script: " + std::string(lua_tostring(L, -1)));
                }
            }
        }
    }

    void Close() {
        if (L) {
            lua_close(L);
            L = nullptr;
        }
    }
}
