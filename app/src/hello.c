#include <stdio.h>
#include <ctype.h>
int main()
{
    printf("Content-Type: text/html");
    printf("\n\n");
    puts("<html><head><title>Hello World</title></head>\n");
    puts("<body><h2><hr>\n");
    puts("<pre>\n");
    puts("</pre><hr>");
    puts("</body>\n");
    puts("</html>\n");
    return 0;
}