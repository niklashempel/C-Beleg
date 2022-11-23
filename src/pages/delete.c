#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/database.h"
#include "../lib/htmlHelper.h"

int main()
{
    char *postdata;
    getPostdata(&postdata);
    
    char *key = strtok(postdata, "=");
    char *value = strtok(NULL, "");
    if (key && (strcmp("id", key) == 0) && value)
    {
        int id = (int)strtol(value, NULL, 10);
        dbDelete(id);
    }
    free(postdata);

    redirect("/");

    return 0;
}