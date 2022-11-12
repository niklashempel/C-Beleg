#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>

#define MAX_ROWS 100
#define MAX_DATA 50

enum TYPE
{
    Book = 0,
    Cd = 1,
    Dvd = 2
};

typedef struct Medium
{
    int id;
    char title[MAX_DATA];
    enum TYPE type;
    char creator[MAX_DATA];
} Medium;

struct Database
{
    struct Medium rows[MAX_ROWS];
};

struct Connection
{
    FILE *file;
    struct Database *db;
};

void die(const char *message);
void print(struct Medium *medium);
void load(struct Connection *conn);
struct Connection *open(const char *filename, char mode);
void close(struct Connection *conn);
void write(struct Connection *conn);
void create(struct Connection *conn);
void set(struct Connection *conn, int id, const char *name, const char *email);
void get(struct Connection *conn, int id);
void removeA(struct Connection *conn, int id);
void list(struct Connection *conn);

#endif // DATABASE