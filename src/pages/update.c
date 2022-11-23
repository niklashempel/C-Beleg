#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/database.h"
#include "../lib/models.h"
#include "../lib/htmlHelper.h"
#include "../lib/query.h"

int main()
{
    int id = getIdFromQueryString();
    char *postdata;
    getPostdata(&postdata);

    char *key;
    char *value;
    char *tempKey;
    Medium medium;
    for (key = strtok(postdata, "&"); key != NULL; key = strtok(key, "&"))
    {
        tempKey = key + strlen(key) + 1;
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
        key = tempKey;
    }

    dbUpdate(id, &medium);
    free(postdata);

    redirect("/");

    return 0;
}