cmake_minimum_required(VERSION 3.30)
project(Calculator C)

set(CMAKE_C_STANDARD 23)

file(GLOB UTIL_SOURCES "util/*.c")
file(GLOB RENDER_SOURCES "render/*.c")
file(GLOB CONTROLLER_SOURCES "controller/*.c")
file(GLOB MODEL_SOURCES "model/*.c")

set(SOURCES main.c
        ${UTIL_SOURCES}
        ${RENDER_SOURCES}
        ${CONTROLLER_SOURCES}
        ${MODEL_SOURCES}
)

add_executable(Calculator ${SOURCES})

target_include_directories(Calculator PRIVATE
        controller
        model
        util
        render
)