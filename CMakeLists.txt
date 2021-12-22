cmake_minimum_required(VERSION 3.21)
project(Asteroids_Cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE)
find_package(SDL2TTF)
find_package(SDL2Mixer)

file(COPY sprites DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(Asteroids_Cpp main.cpp)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
target_link_libraries(Asteroids_Cpp ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})