cmake_minimum_required(VERSION 3.12)

add_executable(default default.c)
add_executable(edit edit.c)
add_executable(delete delete.c)
add_executable(new new.c)
add_executable(create create.c)
add_executable(update update.c)

set(libDatabaseHtmlQuery database html query)

target_link_libraries(default database)
target_link_libraries(default html)
target_link_libraries(new html)
target_link_libraries(edit ${libDatabaseHtmlQuery})
target_link_libraries(delete ${libDatabaseHtmlQuery})
target_link_libraries(create ${libDatabaseHtmlQuery})
target_link_libraries(update ${libDatabaseHtmlQuery})