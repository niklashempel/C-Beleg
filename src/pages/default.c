#include <stdio.h>
#include "../lib/database.h"
#include "../third-party/sqlite3.h"
#include "../lib/html.h"

const char *mediaTypes[] = {"Book", "CD", "DVD"};

int callback(void *, int, char **, char **);

int main()
{
    dbInit();
    printHeader("Media control");

    puts("\
    <table class='table'>\
        <tr>\
            <th colspan='4'>\
                <h3>Media</h3>\
            </th>\
            <td align='right'>\
                <a type='button' class='btn btn-success' href='/new'>New medium</a>\
            </td>\
        </tr>\
    <tr>\
        <th>Name</th>\
        <th>Type</th>\
        <th>Author</th>\
        <th>Borrower</th>\
        <th>Actions</th>\
    </tr>");

    dbRead(callback);

    puts("</table>");
    printFooter();
    return 0;
}

int callback(void *NotUsed, int argc, char **argv,
             char **azColName)
{
    NotUsed = 0;

    puts("<tr>");
    for (int i = 1; i < argc; i++)
    {
        printf("<td>%s</td>\n", argv[i] ? argv[i] : "");
    }
    printf("\
    <td>\
        <div class='btn-toolbar' role='toolbar'>\
            <div class='btn-group me-2' role='group'>\
                <a type='button' class='btn btn-primary' href='/edit?id=%s'>Edit</a>\
            </div>\
            <form action='/delete' method='post' style='margin-block-end: 0em'>\
                <div class='form-group'>\
                <input type='hidden' value='%s' id='id' name='id'>\
                <div class='btn-group me-2' role='group'>\
                    <button type='submit' class='btn btn-danger'>Delete</button>\
                </div>\
                </div>\
            </form>\
        </div>\
    </td>",
           argv[0], argv[0]);

    printf("</tr>");

    return 0;
}