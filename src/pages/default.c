#include <stdio.h>
#include "../lib/database.h"
#include "../third-party/sqlite3.h"

const char *mediaTypes[] = {"Book", "CD", "DVD"};

int callback(void *, int, char **, char **);

int main()
{
    dbInit();

    printf("Content-Type: text/html");
    printf("\n\n");
    puts("<html>\n");
    puts("<head>\n");
    puts("<title>Hello World</title>\n");
    puts("<link href='https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-Zenh87qX5JnK2Jl0vWa8Ck2rdkQ2Bzep5IDxbcnCeuOxjzrPF/et3URy9Bv1WTRi' crossorigin='anonymous'>\n");

    puts("</head>\n");
    puts("<body>\n");
    puts("<table class='table'>\n");
    puts("<tr>\n");
    puts("<th>Name</th>\n");
    puts("<th>Type</th>\n");
    puts("<th>Author</th>\n");
    puts("<th></th>\n");
    puts("</tr>\n");

    dbRead(callback);
    puts("</table>\n");
    puts("<script src='https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/js/bootstrap.bundle.min.js' integrity='sha384-OERcA2EqjJCMA+/3y+gxIOqMEjwtxJY7qPCqsdltbNJuaOe923+mo//f6V8Qbsw3' crossorigin='anonymous'></script>\n");
    ;
    puts("</body>\n");
    puts("</html>\n");
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
                <a role='button' class='btn btn-primary' href='/edit?id=%s'>Edit</a>\
            </div>\
            <div class='btn-group me-2' role='group'>\
                <button type='button' class='btn btn-danger'>Delete</button>\
            </div>\
        </div>\
    </td>",
           argv[0]);

    printf("</tr>\n");
    printf("\n");

    return 0;
}