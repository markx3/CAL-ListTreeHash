listmake: list/main.c list/list.c
	gcc -o list/exec list/main.c list/list.c

treemake: tree/main.c tree/avl.c
	gcc -o tree/exec tree/main.c tree/avl.c

hashmake: hash/main.c hash/hashtable.c hash/list.c
	gcc -o hash/exec hash/main.c hash/hashtable.c hash/list.c

all: listmake treemake hashmake
