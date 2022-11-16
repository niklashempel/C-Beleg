#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>

int dbInit();
int dbRead(int (*callback)(void *, int, char **, char **));
int dbDelete(int id);

enum TYPE
{
    Book = 0,
    Cd = 1,
    Dvd = 2
};

#endif // DATABASE