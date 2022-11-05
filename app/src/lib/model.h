#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>

#define MAX_ROWS 100
#define MAX_DATA 50

enum TYPE
{
  Book = 0,
  Cd = 1,
  Dvd = 2
};

struct Medium
{
  int id;
  char title[MAX_DATA];
  enum TYPE type;
  char creator[MAX_DATA];
};

struct Database
{
  struct Medium rows[MAX_ROWS];
};

struct Connection
{
  FILE *file;
  struct Database *db;
};

#endif MODEL_H
