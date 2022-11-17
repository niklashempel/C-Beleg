#include <stdio.h>
#include "database.h"
#include "../third-party/sqlite3.h"

char dbFileName[] = "test.db";

int dbInit()
{
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open(dbFileName, &db);

    if (rc != SQLITE_OK)
    {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS Media(Id INTEGER PRIMARY KEY AUTOINCREMENT,Name TEXT,Type INT,Creator TEXT,Borrower TEXT);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK)
    {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}

int dbRead(int (*callback)(void *, int, char **, char **))
{
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open(dbFileName, &db);

    if (rc != SQLITE_OK)
    {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "SELECT * FROM Media";

    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK)
    {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}

int dbDelete(int id)
{
    sqlite3 *db;
    sqlite3_stmt *res;

    int rc = sqlite3_open(dbFileName, &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "DELETE FROM Media WHERE Id = @id";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        int idIndex = sqlite3_bind_parameter_index(res, "@id");
        sqlite3_bind_int(res, idIndex, id);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(res);

    if (rc != SQLITE_DONE)
    {
        fprintf(stderr, "Failed to delete data\n");
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));

        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}

int dbCreate(Medium *medium)
{
    sqlite3 *db;
    sqlite3_stmt *res;

    int rc = sqlite3_open(dbFileName, &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "INSERT INTO Media (Name,Type,Creator,Borrower) VALUES(?, ?, ?, ?);";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        // Bind parameter index starts at 1.
        sqlite3_bind_text(res, 1, medium->name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 2, medium->type);
        sqlite3_bind_text(res, 3, medium->creator, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(res, 4, medium->borrower, -1, SQLITE_TRANSIENT);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(res);

    if (rc != SQLITE_DONE)
    {
        fprintf(stderr, "Failed to insert data\n");
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));

        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}