/*
 * query.h
 * 2023-1-15
 * Author: Niklas Hempel
 */
#include "models.h"

int getIdFromQueryString();
void getRequestBody(char **body);
void parseRequestBody(char *body, Medium *medium);
void parseFilterQuery(Filter *filter);
RequestMethod getRequestMethod();