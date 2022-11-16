#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/database.h"

int main()
{
    char *len_ = getenv("CONTENT_LENGTH");
    long len = strtol(len_, NULL, 10);
    char *postdata = malloc(len + 1);

    if (!postdata)
    {
        return 1;
    }

    fgets(postdata, len + 1, stdin);
    char *key = strtok(postdata, "=");
    char *value = strtok(NULL, "");
    if (key && (strcmp("id", key) == 0) && value)
    {
        int id = (int)strtol(value, NULL, 10);
        dbDelete(id);
    }
    free(postdata);

    printf("Location: /\n\n");

    return 0;
}