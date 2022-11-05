#include <stdio.h>
#include <ctype.h>


const char *mediaTypes[] = {"Book", "CD", "DVD"};

int main()
{
    struct Medium media[5];

    for (int i = 0; i < sizeof media / sizeof media[0]; i++)
    {
        media[i].type = i % 3;
        sprintf(media[i].title, "%d", i);
        sprintf(media[i].creator, "Name%d", i);
    }

    printf("Content-Type: text/html"); 
    printf("\n\n");
    puts("<html><head><title>Hello World</title>\n");
    // puts('<link rel="stylesheet" type="text/css" href="../default.css"/>\n');
    puts("</head>\n");
    puts("<body>\n");
    puts("<table>\n");
    puts("<tr>\n");
    puts("<th>Name</th>\n");
    puts("<th>Type</th>\n");
    puts("<th>Author</th>\n");
    puts("</tr>\n");

    for (int i = 0; i < sizeof media / sizeof media[0]; i++)
    {
        puts("<tr>\n");
        printf("<td>%s</td>\n", media[i].title);
        printf("<td>%s</td>\n", mediaTypes[media[i].type]);
        printf("<td>%s</td>\n", media[i].author.name);
        printf("<tr>\n");
    }

    puts("</table>\n");
    puts("</body>\n");
    puts("</html>\n");
    return 0;
}