cmake_minimum_required(VERSION 3.1...3.29)

project(
    bds_btb
    VERSION 3.3.0
    DESCRIPTION "BDS for Minecraft: Pocket Edition 1.1.x"
    LANGUAGES CXX
)

add_executable(
    bds_btb
    src/main.cpp
 "src/pch.cpp" "src/pch.h" "src/event/types/servertick.h")
