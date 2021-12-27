cmake_minimum_required(VERSION 3.21)
project(Asteroids_Cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_IMAGE)
find_package(SDL2TTF)

file(COPY sprites DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(Asteroids_Cpp src/App.cpp src/Player.cpp src/Player.h src/Utilities.cpp src/Utilities.h src/Bullet.cpp src/Bullet.h src/Game.cpp src/Game.h src/GameObject.h src/Asteroid.cpp src/Asteroid.h src/Menu.cpp src/Menu.h src/Scene.h src/Score.cpp src/Score.h)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2TTF_INCLUDE_DIR})
target_link_libraries(Asteroids_Cpp ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2TTF_LIBRARY})