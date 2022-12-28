#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "models.h"

void replace(char *s, char ch, char *repl)
{
    if(s)
    {
        for(char *t=s; *t; t++)
        {
            if(*t == ch)
            {
                memcpy(s, repl, 1);
                s++;
            }
            else
            {
                *s = *t;
                s++;
            }
        }
    }
    
}

int getIdFromQueryString()
{
    char *query = getenv("QUERY_STRING");
    char *key = strtok(query, "=");
    char *value = strtok(NULL, "");
    int id = atoi(value);

    return id;
}

void getRequestBody(char **body)
{
    char *len_ = getenv("CONTENT_LENGTH");
    long len = strtol(len_, NULL, 10);
    *body = malloc(len + 1);

    if (body)
    {
        fgets(*body, len + 1, stdin);
    }
}

void parseRequestBody(char *body, Medium *medium)
{
    char *key;
    char *value;
    char *tempKey;
    for (key = strtok(body, "&"); key != NULL; key = strtok(key, "&"))
    {
        tempKey = key + strlen(key) + 1;
        key = strtok(key, "=");

        if (strcmp(key, "name") == 0)
        {
            value = strtok(NULL, "=");
            replace(value, '+', " ");
            medium->name = value ? value : "";
        }
        else if (strcmp(key, "type") == 0)
        {
            value = strtok(NULL, "=");
            medium->type = atoi(value);
        }
        else if (strcmp(key, "creator") == 0)
        {
            value = strtok(NULL, "=");
            replace(value, '+', " ");
            medium->creator = value ? value : "";
        }
        else if (strcmp(key, "borrower") == 0)
        {
            value = strtok(NULL, "=");
            replace(value, '+', " ");
            medium->borrower = value ? value : "";
        }

        // We store the original key because strtok() destroys the original string.
        key = tempKey;
    }
}

void parseFilterQuery(Filter *filter)
{
    char *body = getenv("QUERY_STRING");
    char *key;
    char *value;
    char *tempKey;
    for (key = strtok(body, "&"); key != NULL; key = strtok(key, "&"))
    {
        tempKey = key + strlen(key) + 1;
        key = strtok(key, "=");

        if (strcmp(key, "name") == 0)
        {
            value = strtok(NULL, "=");
            filter->name = value == NULL ? "" : value;
        }
        else if (strcmp(key, "borrower") == 0)
        {
            value = strtok(NULL, "=");
            filter->borrower = value == NULL ? "" : value;
        }

        // We store the original key because strtok() destroys the original string.
        key = tempKey;
    }
}

RequestMethod getRequestMethod()
{
    char *method;
    RequestMethod request;
    method = getenv("REQUEST_METHOD");
    if (strcmp(method, "GET") == 0)
    {
        return GET;
    }
    else if (strcmp(method, "POST") == 0)
    {
        return POST;
    }
    else
    {
        return Unknown;
    }

    return request;
}