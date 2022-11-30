#ifndef DATABASE_H
#define DATABASE_H
#include "models.h"

int dbInit();
int dbRead(int (*callback)(void *, int, char **, char **));
int dbDelete(int id);
int dbCreate(Medium *medium);
int dbFind(int id, int (*callback)(int id, char *name, int type, char *creator, char *borrower));
int dbUpdate(int id, Medium *medium);
int dbFilter(Filter *filter, int (*callback)(int id, char *name, int type, char *creator, char *borrower));

#endif // DATABASE