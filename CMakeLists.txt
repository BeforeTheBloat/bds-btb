cmake_minimum_required(VERSION 3.11)
project(bds_btb VERSION 3.3.0 DESCRIPTION "BDS for Minecraft: Pocket Edition 1.1.x" LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    lua
    GIT_REPOSITORY https://github.com/lua/lua.git
    GIT_TAG master
)
FetchContent_GetProperties(lua)
if(NOT lua_POPULATED)
    FetchContent_Populate(lua)

    set(LUA_INCLUDE_DIR "${lua_SOURCE_DIR}")

    if(EXISTS "${LUA_INCLUDE_DIR}/lua.h")
        message(STATUS "Found lua.h in ${LUA_INCLUDE_DIR}")
    else()
        message(FATAL_ERROR "Cannot find lua.h in ${LUA_INCLUDE_DIR}")
    endif()

    file(GLOB LUA_SOURCES "${LUA_INCLUDE_DIR}/*.c")
    list(REMOVE_ITEM LUA_SOURCES "${LUA_INCLUDE_DIR}/onelua.c")

    add_library(liblua STATIC ${LUA_SOURCES})
    target_include_directories(liblua PUBLIC "${LUA_INCLUDE_DIR}")

    add_library(lua_library INTERFACE)
    target_include_directories(lua_library INTERFACE "${LUA_INCLUDE_DIR}")
    add_dependencies(lua_library liblua)
endif()

add_executable(bds_btb 
    src/main.cpp
    src/pch.cpp
    src/lua/scripting.cpp
    src/logger/logger.cpp
    src/event/event.cpp
    src/minecraft/network/socket_abstraction.cpp
)

target_link_libraries(bds_btb PRIVATE liblua lua_library)

if(MSVC)
    target_link_libraries(bds_btb PRIVATE ws2_32)
    target_precompile_headers(bds_btb PRIVATE src/pch.h)
endif()
