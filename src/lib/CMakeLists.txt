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

add_library(
    query
    query.h
    query.c
)

target_link_libraries(database sqlite3)
