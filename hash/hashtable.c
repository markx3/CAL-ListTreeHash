#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "list.h"

// Initializes hashtable.
hashtable_t *hash_init(int table_s) {
	hashtable_t *h = NULL;
	if ((h = malloc(sizeof(hashtable_t))) == NULL)
		return NULL;
	if ((h->table = malloc(sizeof(hash_ele_t)*table_s)) == NULL)
		return NULL;
	int i = 0;
	for (i = 0; i < table_s; i++) {
		h->table[i].element = NULL;
		//&h->table[i].list = NULL;
	}
	t_size = table_s;
	return h;
}

/*
hash_ele_t *hash_ele_init(element_t *element) {
	hash_ele_t *h_ele = NULL;
	if ((h_ele = malloc(sizeof(hash_ele_t))) == NULL)
		return NULL;
	h->element = element;
	list_init(h->list);
	return h_ele;
}*/

// Inserts into hashtable. If element position is already occupied, switches to list.
int hash_insert(hashtable_t *h, int index, char *p, char *s) {
	int key = hash_function(p, s);
	if (h->table[key].element == NULL) {
		element_t *e = elloc(index, p, s);
		h->table[key].element = e;
		return 1;
	}
	else {
		//printf("Colisão! Key: %d, Index: %d\n", key, index);
		list_t *l;
		if ((l = &h->table[key].list) == NULL)
			list_init(l);
		list_insert_end(l, index, p, s);
		return 1;
	}
	return 0;
}

// Tries to access table's element based on given key. Looks through list if not in main element vector.
int hash_find(hashtable_t *h, char *p, char *s) {
	int key = hash_function(p, s);
	element_t *ele = h->table[key].element;
	if (ele == NULL)
		return -1;
	if (!(strcmp(ele->p, p)) && !(strcmp(ele->s, s))) {
		return ele->index;
	}
	list_t l = h->table[key].list;
	return list_find(l, p, s);

}

// Hashing
int hash_function(char *p, char *s) {
	char *n = malloc(sizeof(char)*ELE_CHAR*2);
    strcat(n, p);
    strcat(n, s);
    unsigned long hash = 5381;
    int c;
    //printf("key = %s\n", n);
    while (c = *n++) {
        hash = ((((hash << 5) + hash))+ c) ; /* hash * 33 + c */
      }
      //getchar();
      //printf("%lu\n", hash%t_size);

    return hash%t_size;
}
