cmake_minimum_required(VERSION 3.0.0)
project(engine VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

add_library(engine SHARED
  src/Engine.cpp
  src/PhysicsServer.cpp
  src/Postman.cpp
  src/Scene.cpp
  src/SceneController.cpp
  src/Simplex.cpp
  src/CollisionBody.cpp
)

target_include_directories(engine PRIVATE ./include)
target_include_directories(engine PRIVATE ./src)

set(
  CMAKE_CXX_FLAGS
  "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3"
)

find_package(SFML 2 REQUIRED window graphics system)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(engine sfml-window sfml-graphics sfml-system)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
