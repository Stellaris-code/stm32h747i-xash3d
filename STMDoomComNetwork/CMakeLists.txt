cmake_minimum_required(VERSION 3.5)

project(STMDoomComNetwork LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#set(SDL2_PATH "D:/SDL2-devel-2.26.4-VC/SDL2-2.26.4" CACHE BOOL "")
#set(SDL2_NET_PATH "D:/SDL2_net-2.2.0" CACHE BOOL "")

add_definitions(-DSDL_MAIN_HANDLED)

find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)


add_subdirectory(libserialport)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(STMDoomComNetwork main.cpp)
target_link_libraries(STMDoomComNetwork serialport-static SDL2::Net)
