#ifndef DATABASE_H
#define DATABASE_H
#include "model.h"

void die(const char *message);
void print(struct Medium *medium);
void load(struct Connection *conn);
struct Connection *open(const char *filename, char mode);
void close(struct Connection *conn);
void write(struct Connection *conn);
void create(struct Connection *conn);
void set(struct Connection *conn, int id, const char *name, const char *email);
void get(struct Connection *conn, int id);
void delete(struct Connection *conn, int id);
void list(struct Connection *conn);
#endif DATABASE_H