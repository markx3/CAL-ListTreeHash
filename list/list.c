/*
  Author: Marcos Felipe Eipper
  Date: 23/04/2017
*/

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* IMPLEMENTATIONS */

// Initializes list.
void list_init(list_t *l) {
  l->head = NULL;
}

// Returns 1 if list is empty.
int list_empty(list_t l) {
  return l.head == NULL;
}

// Inserts index, first name and second name into the list's first position.
int list_insert_start(list_t *l, int index, char *p, char *s) {
  element_t *ele = elloc(index, p, s);
  if (ele == NULL) return 0; // Failed to allocate element.
  ele->next = l->head;
  l->head = ele;
  return 1; // Success
}

// Inserts index, first name and second name into the list's last position.
int list_insert_end(list_t *l, int index, char *p, char *s) {
  if (list_empty(*l)) return list_insert_start(l, index, p, s);
  element_t *ele = elloc(index, p, s);
  if (ele == NULL) return 0; // Failed to allocate element.
  // Create iterator to go through list
  element_t *iterator = l->head;
  while(iterator->next != NULL)
    iterator = iterator->next;
  iterator->next = ele;
  ele->next = NULL;
  return 1; // Success
}

// Allocates element.
element_t *elloc(int index, char *p, char *s) {
  element_t *ele = malloc(sizeof(element_t));
  if (ele == NULL) return NULL;
  ele->index = index;
  ele->p = malloc(sizeof(char)*ELE_CHAR);
  ele->s = malloc(sizeof(char)*ELE_CHAR);
  strcpy(ele->p, p);  // MIGHT BE ERROR PRONE recheck for strncpy
  strcpy(ele->s, s);
  return ele;
}

// Returns index based on first name and second name.
int list_find(list_t l, char *p, char *s) {
  element_t *iterator = l.head;
  while (iterator != NULL) {
    if (strcmp(iterator->p, p) == 0) {
      if (strcmp(iterator->s, s) == 0) {
        return iterator->index; // Success
      }
    }
    iterator = iterator->next;
  }
  return -1; // Failed
}
