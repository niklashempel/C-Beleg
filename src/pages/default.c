#include <stdio.h>
#include <string.h>
#include "../lib/database.h"
#include "../third-party/sqlite3.h"
#include "../lib/html.h"
#include "../lib/query.h"

const char *mediaTypes[] = {"Book", "CD", "DVD"};

int callback(void *, int, char **, char **);
int filterCallback(int id, char *name, int type, char *creator, char *borrower);

int main()
{
    dbInit();

    Filter filter = {.name = "", .borrower = ""};
    parseFilterQuery(&filter);

    printHeader("Media control");

    printf("\
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
            <td colspan='5'>\
                <form action='/' method='get'>\
                    <div class='row align-items-end'>\
                        <div class='form-group col-md-2'>\
                            <label for='inputName'>Name</label>\
                            <input type='text' class='form-control' id='inputName' placeholder='Medium name' name='name' value='%s'>\
                        </div>\
                        <div class='form-group col-md-2'>\
                            <label for='inputBorrower'>Borrower</label>\
                            <input type='text' class='form-control' id='inputBorrower' placeholder='Borrower name' name='borrower' value='%s'>\
                        </div>\
                        <div class='form-group col-md-2'>\
                            <button type='submit' class='form-group btn btn-primary'>Filter</button>\
                            <a type='button' class='form-group btn btn-info' href='/'>Clear</a>\
                        </div>\
                    </div>\
                  </form>\
            </td>\
        </tr>\
    <tr>\
        <th>Name</th>\
        <th>Type</th>\
        <th>Author</th>\
        <th>Borrower</th>\
        <th>Actions</th>\
    </tr>",
           filter.name, filter.borrower);

    // Check if name and borrower filter are both empty. strcmp return 0 if 2 strings are equal.
    if ((filter.name == NULL && filter.borrower == NULL) || (!strcmp(filter.name, "") && !strcmp(filter.borrower, "")))
    {
        dbRead(callback);
    }
    else
    {
        dbFilter(&filter, filterCallback);
    }

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

int filterCallback(int id, char *name, int type, char *creator, char *borrower)
{
    puts("<tr>");
    printf("<td>%s</td>\n", name);
    printf("<td>%d</td>\n", type);
    printf("<td>%s</td>\n", creator);
    printf("<td>%s</td>\n", borrower);
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
}
