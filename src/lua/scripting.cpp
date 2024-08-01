#include "scripting.h"

namespace fs = std::filesystem;

namespace LuaScripting {
    lua_State* L = nullptr;

    int lua_logger_info(lua_State* L) {
        const char* message = luaL_checkstring(L, 2);
        Logger::LuaInfo(message);
        return 0;
    }

    int lua_logger_success(lua_State* L) {
        const char* message = luaL_checkstring(L, 2);
        Logger::LuaSuccess(message);
        return 0;
    }

    int lua_logger_error(lua_State* L) {
        const char* message = luaL_checkstring(L, 2);
        Logger::LuaError(message);
        return 0;
    }

    void register_logger_functions(lua_State* L) {
        lua_newtable(L);

        lua_pushcfunction(L, lua_logger_info);
        lua_setfield(L, -2, "Info");

        lua_pushcfunction(L, lua_logger_success);
        lua_setfield(L, -2, "Success");

        lua_pushcfunction(L, lua_logger_error);
        lua_setfield(L, -2, "Error");

        lua_setglobal(L, "Logger");
    }

    void Init() {
        L = luaL_newstate();
        luaL_openlibs(L);

        register_logger_functions(L);

        std::string scriptDir = "scripts";
        for (const auto& entry : fs::directory_iterator(scriptDir)) {
            if (entry.path().extension() == ".lua") {
                Logger::Success("Loaded script: " + entry.path().string());
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
