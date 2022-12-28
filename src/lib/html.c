#include <stdio.h>

void printHeader(char *title)
{
    puts("Content-Type: text/html");
    puts("\n\n");
    puts("<html>\n");
    puts("<head>\n");
    printf("<title>%s</title>\n", title);
    puts("<link href='https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-Zenh87qX5JnK2Jl0vWa8Ck2rdkQ2Bzep5IDxbcnCeuOxjzrPF/et3URy9Bv1WTRi' crossorigin='anonymous'>\n");
    puts("</head>\n");
    puts("<body class='m-2'>\n");
}

void printFooter()
{
    puts("<script src='https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/js/bootstrap.bundle.min.js' integrity='sha384-OERcA2EqjJCMA+/3y+gxIOqMEjwtxJY7qPCqsdltbNJuaOe923+mo//f6V8Qbsw3' crossorigin='anonymous'></script>\n");
    puts("</body>\n");
    puts("</html>\n");
}

void redirect(char *url)
{
    printf("Status: 303 See Other\n");
    printf("Location: %s\n", url);
    printf("\n");
}