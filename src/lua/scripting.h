#pragma once

#include "../pch.h"
#include <filesystem>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}


namespace LuaScripting {
    extern lua_State* L;

    void Init();
    void Close();

    int lua_logger_info(lua_State* L);
    int lua_logger_error(lua_State* L);
}