add_library(
    database
    database.h
    database.c
)

add_library(
    htmlHelper
    htmlHelper.h
    htmlHelper.c
)

target_link_libraries(database sqlite3)
