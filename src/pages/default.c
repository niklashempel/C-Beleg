#include <stdio.h>
// #include <ctype.h>
// #include "../lib/model.h"
#include "../lib/database.h"
#include "../third-party/sqlite3.h"

const char *mediaTypes[] = {"Book", "CD", "DVD"};

int callback(void *, int, char **, char **);

int main()
{
    dbInit();

    printf("Content-Type: text/html");
    printf("\n\n");
    puts("<html><head><title>Hello World</title>\n");
    puts("</head>\n");
    puts("<body>\n");
    puts("<table>\n");
    puts("<tr>\n");
    puts("<th>Name</th>\n");
    puts("<th>Type</th>\n");
    puts("<th>Author</th>\n");
    puts("</tr>\n");

    dbRead(callback);

    puts("</table>\n");
    puts("</body>\n");
    puts("</html>\n");
    return 0;
}

int callback(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;
    
            puts("<tr>\n");
    for (int i = 1; i < argc; i++)
    {
        printf("<td>%s</td>\n", argv[i] ? argv[i] : "");
    }
    printf("<td><a href='/edit?id=%d'><div>Edit</div></a></td>", argv[0]);
    printf("</tr>\n");
    printf("\n");
    
    return 0;
}