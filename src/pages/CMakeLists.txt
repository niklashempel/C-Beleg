cmake_minimum_required(VERSION 3.12)

add_executable(default default.c)
add_executable(edit edit.c)
add_executable(delete delete.c)
add_executable(new new.c)

target_link_libraries(default database html query)
target_link_libraries(new database html query)
target_link_libraries(edit database html query)
target_link_libraries(delete database html query)