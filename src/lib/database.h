#ifndef DATABASE_H
#define DATABASE_H
#include "models.h"

int dbInit();
int dbRead(int (*callback)(void *, int, char **, char **));
int dbDelete(int id);
int dbCreate(Medium *medium);

#endif // DATABASE