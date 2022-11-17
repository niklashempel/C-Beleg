cmake_minimum_required(VERSION 3.12)
project(C-Beleg LANGUAGES C VERSION 1.0.0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpthread -ldl")

add_subdirectory(src/lib)
add_subdirectory(src/pages)
add_subdirectory(src/third-party)