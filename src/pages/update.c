#include <stdlib.h>
#include "../lib/database.h"
#include "../lib/models.h"
#include "../lib/html.h"
#include "../lib/query.h"

int main()
{
    int id = getIdFromQueryString();

    char *body;
    getRequestBody(&body);

    Medium medium;
    parseRequestBody(body, &medium);

    dbUpdate(id, &medium);

    free(body);

    redirect("/");

    return 0;
}