add_library(
    database
    database.h
    database.c
)

add_library(
    html
    html.h
    html.c
)

add_library(
    query
    query.h
    query.c
)

target_link_libraries(database sqlite3)
