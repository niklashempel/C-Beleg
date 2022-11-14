add_library(
    database
    database.h
    database.c
)

target_link_libraries(database sqlite3)
