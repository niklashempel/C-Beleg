cmake_minimum_required(VERSION 3.12)

add_executable(default.cgi default.c)
add_executable(edit.cgi edit.c)
add_executable(delete.cgi delete.c)
add_executable(new.cgi new.c)

target_link_libraries(default.cgi database html query)
target_link_libraries(new.cgi database html query)
target_link_libraries(edit.cgi database html query)
target_link_libraries(delete.cgi database html query)