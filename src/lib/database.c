#include <stdio.h>
#include "database.h"
#include "../third-party/sqlite3.h"

char dbFileName[]="test.db";

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

    char *sql = "CREATE TABLE IF NOT EXISTS Media(Id INT PRIMARY KEY,Name TEXT,Type INT,Publisher TEXT,Borrower TEXT);";

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
    char *err_msg = 0;
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
        fprintf(stderr, "Failed to execute statement: %s\n", err_msg);
    }

    int step = sqlite3_step(res);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to delete data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}