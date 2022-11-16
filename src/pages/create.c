#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/database.h"
#include "../lib/models.h"
#include "../lib/htmlHelper.h"

int main()
{
    char *len_ = getenv("CONTENT_LENGTH");
    long len = strtol(len_, NULL, 10);
    char *postdata = malloc(len + 1);
    char *p;
    Medium medium;

    if (!postdata)
    {
        return 1;
    }

    fgets(postdata, len + 1, stdin);

    char *key;
    char *value;
    char *backupKey;
    for (key = strtok(postdata, "&"); key != NULL; key = strtok(key, "&"))
    {
        backupKey = key + strlen(key) + 1;
        key = strtok(key, "=");

        if (strcmp(key, "name") == 0)
        {
            value = strtok(NULL, "=");
            medium.name = value;
        }
        else if (strcmp(key, "type") == 0)
        {
            value = strtok(NULL, "=");
            medium.type = atoi(value);
        }
        else if (strcmp(key, "creator") == 0)
        {
            value = strtok(NULL, "=");
            medium.creator = value;
        }
        else if (strcmp(key, "borrower") == 0)
        {
            value = strtok(NULL, "=");
            medium.borrower = value;
        }

        // We store the original key because strtok() destroys the original string.
        key = backupKey;
    }

    dbCreate(&medium);
    free(postdata);

    redirect("/");

    return 0;
}