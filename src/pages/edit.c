#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *Param;
    char *id;

    puts("Content-Type: text/html\n\n");
    puts("<html><head><title>Edit");
    puts("</title></head><body><h2><hr>\n");
    puts("<pre>");
    Param = malloc(1024); //(len+1);
    Param = getenv("QUERY_STRING");
    // puts(Param);
    id = strstr(Param, "id");
    // p += 4;
    // T = strtol(p, (char **)NULL, 10);
    // p = strstr(Param, "Mon");
    // p += 4;
    // M = strtol(p, (char **)NULL, 10);
    // printf("Tag: %d, Mon: %d<br>", T, M);
    // while (fgets(vBuf, 128, FT))
    // {
    //     sscanf(vBuf, "%d.%d. %[^\n]", &t, &m, Text);
    //     if (T == t && M == m)
    //         printf("%d.%d. :%s<p>", t, m, Text);
    // }
    puts("<p>");
    puts("</pre><hr>");
    puts("</body>\n");
    puts("</html>\n");
    return 0;
}