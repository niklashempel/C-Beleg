#include <stdio.h>
#include "../lib/database.h"
#include "../third-party/sqlite3.h"
#include "../lib/htmlHelper.h"

const char *mediaTypes[] = {"Book", "CD", "DVD"};

int callback(void *, int, char **, char **);

int main()
{
    dbInit();
    printHeader("Hello World");

    puts("<table class='table'>\n");
    puts("<tr>\n");
    puts("<th>Name</th>\n");
    puts("<th>Type</th>\n");
    puts("<th>Author</th>\n");
    puts("<th>Borrower</th>\n");
    puts("<th>Actions</th>\n");
    puts("</tr>\n");

    dbRead(callback);
    puts("</table>\n");
    puts("\
    <div class='position-absolute bottom-0 end-0'>\
        <a type='button' class='btn btn-secondary' href='/new' style='\
            width: 30px;\
            width: 70px;\
            height: 70px;\
            padding: 10px 16px;\
            border-radius: 35px;\
            font-size: 24px;\
            text-align: center;'>+</a>\
    </div>");
    printFooter();
    return 0;
}

int callback(void *NotUsed, int argc, char **argv,
             char **azColName)
{

    NotUsed = 0;

    puts("<tr>\n");
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

    printf("</tr>\n");
    printf("\n");

    return 0;
}