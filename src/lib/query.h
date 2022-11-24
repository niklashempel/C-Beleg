#include "models.h"

int getIdFromQueryString();
void getRequestBody(char **body);
void parseRequestBody(char *body, Medium *medium);
void parseFilterQuery(Filter *filter);