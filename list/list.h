/*
  Author: Marcos Felipe Eipper
  Date: 23/04/2017
*/

#ifndef _LIST_H
#define _LIST_H
#define ELE_CHAR 80

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct ele {
  int index;
  char *p;
  char *s;
  struct ele *next;
} element_t;

typedef struct {
  element_t *head;
  element_t *tail;
} list_t;

void list_init(list_t *l);
int list_empty(list_t l);
int list_insert_start(list_t *l, int index, char *p, char *s);
int list_insert_end(list_t *l, int index, char *p, char *s);
element_t *elloc(int index, char *p, char *s);
int list_find(list_t l, char *p, char *s);

#endif /* _LIST_H */
