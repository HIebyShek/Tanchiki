cmake_minimum_required(VERSION 3.0.0)
project(tanks VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

add_executable(tanks 
  src/main.cpp
  src/Background.cpp
  src/LevelScene.cpp
  src/Tank.cpp
  src/Bullet.cpp
  src/Wall.cpp
  src/config.cpp
)

target_include_directories(tanks PRIVATE ./include)
target_include_directories(tanks PRIVATE ./src)
target_include_directories(tanks PRIVATE ../Engine/include)

set(
  CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3"
)

find_package(SFML 2 REQUIRED window graphics system)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} sfml-window sfml-graphics sfml-system)
target_link_libraries(tanks engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)