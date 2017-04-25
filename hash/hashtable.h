#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include "list.h"

int t_size;

typedef struct {
	list_t list;
	element_t *element;	
} hash_ele_t;

typedef struct {
	hash_ele_t *table;
} hashtable_t;

hashtable_t *hash_init(int table_s);
hash_ele_t *hash_ele_init(element_t *element);
int hash_insert(hashtable_t *h, int index, char *p, char *s);
int hash_find(hashtable_t *h, char *p, char *s);
int hash_function(char *p, char *s);

#endif /* _HASHTABLE_H */