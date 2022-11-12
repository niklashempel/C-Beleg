#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "database.h"

void die(const char *message)
{
    if (errno)
    {
        perror(message);
    }
    else
    {
        printf("ERROR: %s\n", message);
    };
    exit(1);
}

void print(struct Medium *medium)
{
    puts("<tr>\n");
    printf("<td>%s</td>\n", medium->title);
    printf("<td>%s</td>\n", medium->type);
    printf("<td>%s</td>\n", medium->creator);
    printf("<tr>\n");
}

void load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
    {
        die("Failed to load database.");
    }
}

struct Connection *open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
        die("Memory error");

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
        die("Memory error");

    if (mode == 'c')
    {
        conn->file = fopen(filename, "w");
    }
    else
    {
        conn->file = fopen(filename, "r+");
        if (conn->file)
        {
           // Database_load(conn);
        }
    }
    return conn;
}

void close(struct Connection *conn)
{
    if (conn)
    {
        if (conn->file)
        {
            fclose(conn->file);
        }
        if (conn->db)
        {
            free(conn->db);
        }
        free(conn);
    }
}

void write(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
    {
        die("Failed to write database");
    }

    rc = fflush(conn->file);
    if (rc == -1)
    {
        die("Cannot flush database");
    }
}

void create(struct Connection *conn)
{
    int i = 0;
    for (i = 0; i < MAX_ROWS; i++)
    {
        // make a prototype to initialize it
        struct Medium medium = {.id = i, .type = 0};
        // then just assign it
        conn->db->rows[i] = medium;
    }
}

void set(struct Connection *conn, int id, const char *name, const char *email)
{
    // struct Medium *medium = &conn->db->rows[id];
    // if (medium->set)
    //     die("Already set, delete it first");

    // medium-> = 1;
    // // WARNING: bug, read the "How to BREAK IT" and fix this
    // char *res = strncpy(medium->name, name, MAX_DATA);
    // // demonstrate the strncpy bug
    // if (!res)
    //     die("Name copy failed!");

    // res = strncpy(medium->email, email, MAX_DATA);
    // if (!res)
    //     die("Email copy failed!");
}

void get(struct Connection *conn, int id)
{
    struct Medium *medium = &conn->db->rows[id];

    if (medium->id)
    {
        print(medium);
    }
    else
    {
        die("ID is not set");
    }
}

void removeA(struct Connection *conn, int id)
{
    struct Medium medium = {.id = id, .type = 0};
    conn->db->rows[id] = medium;
};

void list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < MAX_ROWS; i++)
    {
        struct Medium *cur = &db->rows[i];

        if (cur->id)
        {
            print(cur);
        }
    }
}