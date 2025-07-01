cmake_minimum_required(VERSION 4.0.0)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER clang++) # NOTE: must declare before `project()`
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(arkanoid.cpp VERSION 1.0.0 LANGUAGES CXX)

add_executable(arkanoid.cpp)

target_compile_options(arkanoid.cpp PRIVATE -g -O0 -m64 -Wall -Wextra -pedantic)
target_link_options(arkanoid.cpp PRIVATE -m64)

file(GLOB_RECURSE CPP_SOURCES src/*.cpp)
target_sources(arkanoid.cpp PRIVATE ${CPP_SOURCES})

file(GLOB_RECURSE MODULE_SOURCES src/*.cppm configs.cppm)
target_sources(arkanoid.cpp PRIVATE FILE_SET CXX_MODULES FILES ${MODULE_SOURCES})

target_link_libraries(arkanoid.cpp PRIVATE
    allegro_primitives
    allegro_color
    allegro_font
    allegro_ttf
    allegro
)
