#ifndef MODELS_H
#define MODELS_H

typedef enum TYPE
{
    Book = 0,
    Cd = 1,
    Dvd = 2
} TYPE;

typedef struct Medium
{
    int id;
    char *name;
    TYPE type;
    char *creator;
    char *borrower;
} Medium;

typedef struct Filter
{
    char *name;
    char *borrower;
} Filter;

typedef enum RequestMethod
{
    Unknown,
    GET,
    POST
} RequestMethod;

#endif // Models