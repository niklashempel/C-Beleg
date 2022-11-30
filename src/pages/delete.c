#include <stdlib.h>
#include <string.h>
#include "../lib/database.h"
#include "../lib/html.h"
#include "../lib/query.h"

int main()
{
    char *body;
    getRequestBody(&body);

    if (body)
    {
        // Get id from body.
        char *key = strtok(body, "=");
        char *value = strtok(NULL, "");
        if (key && (strcmp("id", key) == 0) && value != NULL)
        {
            int id = (int)strtol(value, NULL, 10);
            dbDelete(id);
        }
        free(body);
    }

    redirect("/");

    return 0;
}