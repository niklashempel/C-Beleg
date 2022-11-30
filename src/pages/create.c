#include <stdlib.h>
#include "../lib/database.h"
#include "../lib/models.h"
#include "../lib/html.h"
#include "../lib/query.h"

int main()
{
    char *body;
    getRequestBody(&body);

    if (body)
    {
        Medium medium;
        parseRequestBody(body, &medium);

        dbCreate(&medium);

        free(body);
    }

    redirect("/");

    return 0;
}