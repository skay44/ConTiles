cmake_minimum_required(VERSION 3.30)
project(ConTiles C)

set(CMAKE_C_STANDARD 23)

file(GLOB UTIL_SOURCES "util/*.c")
file(GLOB RENDER_SOURCES "render/*.c")
file(GLOB CONTROLLER_SOURCES "controller/*.c")
file(GLOB MODEL_SOURCES "model/*.c")
file(GLOB LOGGER "logger/*.c")

set(SOURCES main.c
        ${UTIL_SOURCES}
        ${RENDER_SOURCES}
        ${CONTROLLER_SOURCES}
        ${MODEL_SOURCES}
        ${LOGGER}
)

add_executable(ConTiles ${SOURCES})

target_include_directories(ConTiles PRIVATE
        controller
        model
        util
        render
        logger
)