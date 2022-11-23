#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int getIdFromQueryString(){
    char *query;
    query = getenv("QUERY_STRING");
    char *key = strtok(query, "=");
    char *value = strtok(NULL, "");
    int id = atoi(value);
    
    return id;
}

void getPostdata(char **postdata){
    char *len_ = getenv("CONTENT_LENGTH");
    long len = strtol(len_, NULL, 10);
    *postdata = malloc(len + 1);

    fgets(*postdata, len + 1, stdin);
}