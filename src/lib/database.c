#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int dbFind(int id, Medium *medium)
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

    char *sql = "SELECT * FROM Media WHERE Id = @id";

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

    if (rc == SQLITE_ROW)
    {
        medium->id = (int)sqlite3_column_int(res, 0);
        medium->name = (char *)sqlite3_column_text(res, 1);
        medium->type = (int)sqlite3_column_int(res, 2);
        medium->creator = (char *)sqlite3_column_text(res, 3);
        medium->borrower = (char *)sqlite3_column_text(res, 4);
    }
    else if (rc == SQLITE_DONE)
    {
        fprintf(stderr, "Failed to select data with id %d\n", id);

        sqlite3_close(db);

        return 1;
    }
    else
    {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));

        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}

int dbUpdate(int id, Medium *medium)
{
    sqlite3 *db;
    sqlite3_stmt *res;

    int rc = sqlite3_open(dbFileName, &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stdout, "Cannot open database: %s\n", sqlite3_errmsg(db));

        sqlite3_close(db);

        return 1;
    }

    char *sql = "UPDATE Media set Name = ?, Type = ?, Creator = ?, Borrower = ? WHERE Id = ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {
        sqlite3_bind_text(res, 1, medium->name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 2, medium->type);
        sqlite3_bind_text(res, 3, medium->creator, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(res, 4, medium->borrower, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(res, 5, id);
    }
    else
    {
        fprintf(stdout, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    rc = sqlite3_step(res);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to update data\n");
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));

        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}

int dbFilter(Filter *filter)
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

    char *sql = "SELECT * FROM Media WHERE Name like ? AND Borrower like ?";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK)
    {

        char *name;
        prepareFilter(&name, filter->name);

        char *borrower;
        prepareFilter(&borrower, filter->borrower);

        sqlite3_bind_text(res, 1, name, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(res, 2, borrower, -1, SQLITE_TRANSIENT);

        free(name);
        free(borrower);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int argc = sqlite3_column_count(res);

    if (sqlite3_step(res) == SQLITE_ROW)
    {
        do
        {
            puts("<tr>");
            int id = sqlite3_column_int(res, 0);
            printf("<td>%s</td>\n", (char *)sqlite3_column_text(res, 1));
            printf("<td>%d</td>\n", sqlite3_column_int(res, 2));
            printf("<td>%s</td>\n", (char *)sqlite3_column_text(res, 3));
            printf("<td>%s</td>\n", (char *)sqlite3_column_text(res, 4));
            printf("\
                    <td>\
                        <div class='btn-toolbar' role='toolbar'>\
                            <div class='btn-group me-2' role='group'>\
                                <a type='button' class='btn btn-primary' href='/edit?id=%d'>Edit</a>\
                            </div>\
                            <form action='/delete' method='post' style='margin-block-end: 0em'>\
                                <div class='form-group'>\
                                <input type='hidden' value='%d' id='id' name='id'>\
                                <div class='btn-group me-2' role='group'>\
                                    <button type='submit' class='btn btn-danger'>Delete</button>\
                                </div>\
                                </div>\
                            </form>\
                        </div>\
                    </td>",
                   id, id);

            printf("</tr>");
        } while (sqlite3_step(res) == SQLITE_ROW);
    }
    else if (rc == SQLITE_DONE)
    {
        sqlite3_close(db);

        return 0;
    }
    else
    {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));

        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}

void prepareFilter(char **concatenated, char *source)
{
    char percent = '%';
    size_t len = strlen(source);

    // Two for the extra chars, one for the null terminator
    *concatenated = malloc(len + 2 + 1);
    snprintf(*concatenated, "%c%s%c", percent, source, percent);
}