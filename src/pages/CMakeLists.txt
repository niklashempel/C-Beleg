cmake_minimum_required(VERSION 3.12)

add_executable(default default.c)
add_executable(edit edit.c)

target_link_libraries(default database)
target_link_libraries(edit database)