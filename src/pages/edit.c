#include <stdio.h>
#include <stdlib.h>
#include "../lib/database.h"
#include "../lib/models.h"
#include "../lib/html.h"
#include "../lib/query.h"

int main()
{
    int id = getIdFromQueryString();

    printHeader("Edit");
    
    dbFind(id);
    
    printFooter();

    return 0;
}