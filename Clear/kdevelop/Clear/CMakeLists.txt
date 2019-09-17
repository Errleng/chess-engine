cmake_minimum_required(VERSION 3.0)

project(clear)

file(GLOB clear_SRC
    "*.h"
    "*.cpp"
)

add_executable(clear ${clear_SRC})

install(TARGETS clear RUNTIME DESTINATION bin)
