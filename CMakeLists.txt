cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # export the compiled commands in json

set(PROJECT_NAME tbnl) # project name
project(${PROJECT_NAME} VERSION 0.001)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)
pkg_check_modules(SDL2IMAGE REQUIRED IMPORTED_TARGET SDL2_image)

file(GLOB SOURCES "src/*.c") # find all .c files in src dir

add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories for headers
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
# Linking SDL2 and SDL2_image
target_link_libraries(${PROJECT_NAME} PkgConfig::SDL2 PkgConfig::SDL2IMAGE)

# Debug messages to check configurations
message("SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
message("SDL2_image include dirs: ${SDL2IMAGE_INCLUDE_DIRS}")
