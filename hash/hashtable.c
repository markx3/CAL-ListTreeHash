#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "list.h"

// Initializes hashtable.
hashtable_t *hash_init(int table_s) {
	hashtable_t *h = NULL;
	if ((h = malloc(sizeof(hashtable_t))) == NULL)
		return NULL;
	if ((h->table = malloc(sizeof(list_t)*table_s)) == NULL)
		return NULL;
	int i = 0;
	for (i = 0; i < table_s; i++) {
		list_init(&h->table[i]);
	}
	t_size = table_s;
	return h;
}

// Inserts into hashtable. If element position is already occupied, switches to list.
int hash_insert(hashtable_t *h, int index, char *p, char *s) {
	int key = hash_function(p, s);
	list_insert_end(&h->table[key], index, p, s);
	return 1;
}

// Tries to access table's element based on given key. Looks through list if not in main element vector.
int hash_find(hashtable_t *h, char *p, char *s) {
	int key = hash_function(p, s);
	return list_find(h->table[key], p, s);

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
