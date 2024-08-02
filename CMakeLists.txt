cmake_minimum_required(VERSION 3.11)
project(bds_btb VERSION 3.3.0 DESCRIPTION "BDS for Minecraft: Pocket Edition 1.1.x" LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch Lua
FetchContent_Declare(
    lua
    GIT_REPOSITORY https://github.com/lua/lua.git
    GIT_TAG master
)

# Fetch RakNet
FetchContent_Declare(
    raknet
    GIT_REPOSITORY https://github.com/BeforeTheBloat/RakNet.git
    GIT_TAG master
)

# Fetch nlohmann/json
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2 # Adjust the version as needed
)

# Fetch Base64
FetchContent_Declare(
    base64
    GIT_REPOSITORY https://github.com/ReneNyffenegger/cpp-base64.git
    GIT_TAG master
)

# Populate Lua
FetchContent_GetProperties(lua)
if(NOT lua_POPULATED)
    FetchContent_Populate(lua)
    set(LUA_INCLUDE_DIR "${lua_SOURCE_DIR}")
    file(GLOB LUA_SOURCES "${LUA_INCLUDE_DIR}/*.c")
    list(REMOVE_ITEM LUA_SOURCES "${LUA_INCLUDE_DIR}/onelua.c")
    add_library(liblua STATIC ${LUA_SOURCES})
    target_include_directories(liblua PUBLIC "${LUA_INCLUDE_DIR}")
    add_library(lua_library INTERFACE)
    target_include_directories(lua_library INTERFACE "${LUA_INCLUDE_DIR}")
    add_dependencies(lua_library liblua)
endif()

# Populate RakNet
FetchContent_GetProperties(raknet)
if(NOT raknet_POPULATED)
    FetchContent_Populate(raknet)
    set(RAKNET_INCLUDE_DIR "${raknet_SOURCE_DIR}/Source")
    file(GLOB RAKNET_SOURCES
        "${raknet_SOURCE_DIR}/Source/*.cpp"
        "${raknet_SOURCE_DIR}/Source/*.h"
    )
    add_library(libraknet STATIC ${RAKNET_SOURCES})
    target_include_directories(libraknet PUBLIC "${RAKNET_INCLUDE_DIR}")
endif()

# Populate nlohmann/json
FetchContent_GetProperties(nlohmann_json)
if(NOT nlohmann_json_POPULATED)
    FetchContent_Populate(nlohmann_json)
endif()

# Populate Base64
FetchContent_GetProperties(base64)
if(NOT base64_POPULATED)
    FetchContent_Populate(base64)
endif()

# Add the executable
add_executable(bds_btb 
    src/main.cpp
    src/pch.cpp
    src/lua/scripting.cpp
    src/logger/logger.cpp
    src/event/event.cpp
    ${base64_SOURCE_DIR}/base64.cpp
)

# Link libraries
target_link_libraries(bds_btb PRIVATE liblua lua_library libraknet)

# Include directories
target_include_directories(bds_btb PRIVATE ${nlohmann_json_SOURCE_DIR}/include)
target_include_directories(bds_btb PRIVATE ${base64_SOURCE_DIR})

# MSVC specific settings
if(MSVC)
    target_link_libraries(bds_btb PRIVATE ws2_32)
    target_precompile_headers(bds_btb PRIVATE src/pch.h)
endif()
