/*
  Author: Marcos Felipe Eipper
  Date: 23/04/2017
*/

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "avl.h"

int num_elements;

int main(int argc, char *argv[]) {

  if (argc <= 1) {
    printf("ERRO! Indique qual entrada utilizar.\nExemplo: ./exec entrada-1.txt\n");
    exit(EXIT_FAILURE);
  }

  /* SOME VARS */
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *tok;
  int num_ele;
  FILE *stream;
  FILE *output;
  clock_t start, stop;
  double elapsed;
  char out[ELE_CHAR] = "tree_saida";

  /* FILE HANDLING */
  stream = fopen(argv[1], "r");
  strcat(out, argv[1]);
  //printf("Saída: %s\n\n", out);
  output = fopen(out, "w");
  if (stream == NULL || output == NULL)
    exit(EXIT_FAILURE);

  /* GETTING ENTRY No. */
  getline(&line, &len, stream);
  int num = atoi(line); // Number of entries
  num_elements = num_ele = num;

  /* DECLARING AVL */
  avl_tree_t *t;
  t = avl_tree_init();

  /* INPUT TREATMENT & LIST INSERTION */
  //printf("Inserindo %d elementos na árvore.\n", num_ele);
  start = clock();
  while (num-- > 0) {
    int index;
    char *p;
    char *s;
    p = malloc(sizeof(char)*ELE_CHAR);
    s = malloc(sizeof(char)*ELE_CHAR);

    if ((read = getline(&line, &len, stream)) == -1) break;
    tok = strtok(line, " ");
    index = atoi(tok);
    //printf("index: %d ", index);
    tok = strtok(NULL, " ");
    strcpy(p, tok);
    //printf("p = %s ", p);
    tok = strtok(NULL, " ");
    strcpy(s, tok);
    //printf("s = %s\n", s);

    element_t *ele = element_init(index, p, s);
    //int key = (int)calc_key(p, s);
    //printf("key = %d\n", key);
    avl_insert(t, calc_key(p, s), ele);
  }
  stop = clock();
  elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
  printf("INSERT [%d] TREE: %.2lfms\n", num_ele, elapsed);


    getline(&line, &len, stream);
    num = atoi(line); // Number of searches
    num_ele = num;

    //avl_balance(t);

    /* SEARCHING ELEMENTS */
    //printf("Procurando elementos na árvore.\n");
    start = clock();
    while (num-- > 0) {
      char *p = malloc(sizeof(char)*ELE_CHAR);
      char *s = malloc(sizeof(char)*ELE_CHAR);

      if ((read = getline(&line, &len, stream)) == -1) break;
      tok = strtok(line, " ");
      strcpy(p, tok);
      tok = strtok(NULL, " ");
      strcpy(s, tok);

      fprintf(output, "%d\n", avl_find(t, calc_key(p, s))->element->index);
    }
    stop = clock();
    elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("SEARCH [%d] TREE: %.2lfms\n", num_ele, elapsed);

    /* CLOSING STUFF */
    fclose(stream);
    fclose(output);

    return 0;
  }

  char *calc_key(char *p, char *s) {
    char *n = malloc(sizeof(char)*ELE_CHAR*2);
    strcat(n, p);
    strcat(n, s);
    /*unsigned long hash = 1;
    int c;
    //printf("key = %s\n", n);
    while (c = *n++) {
        //printf("%lu\n", hash);
        hash = ((((hash << 1) * hash))+ c) ; /* hash * 33 + c */
      //}
      //printf("%lu\n", hash);
      //getchar();
    //printf("%s\n", n);
    return n;
    //return hash;
}
    // hash function usada: djb2 (http://www.cse.yorku.ca/~oz/hash.html)
