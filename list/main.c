/*
  Author: Marcos Felipe Eipper
  Date: 23/04/2017
*/

/* INCLUDES */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

int main(int argc, char *argv[]) {
  /* SOME VARS */
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  char *tok;
  FILE *stream;
  FILE *output;
  clock_t start, stop;
  double elapsed;
  char out[ELE_CHAR] = "list_saida";

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
  int num_ele = num;

  /* DECLARING LIST */
  list_t l;
  list_init(&l);

  /* INPUT TREATMENT & LIST INSERTION */
  //printf("Inserindo %d elementos na lista.\n", num_ele);
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

    list_insert_end(&l, index, p, s);
  }
  stop = clock();
  elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
  printf("INSERT [%d] LIST: %.2lfms\n", num_ele, elapsed);

  getline(&line, &len, stream);
  num = atoi(line); // Number of searches
  num_ele = num;

  /* SEARCHING ELEMENTS */
  //printf("Procurando elementos na lista.\n");
  start = clock();
  while (num-- > 0) {
    char *p = malloc(sizeof(char)*ELE_CHAR);
    char *s = malloc(sizeof(char)*ELE_CHAR);

    if ((read = getline(&line, &len, stream)) == -1) break;
    tok = strtok(line, " ");
    strcpy(p, tok);
    tok = strtok(NULL, " ");
    strcpy(s, tok);

    fprintf(output, "%d\n", list_find(l, p, s));
  }
  stop = clock();
  elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
  printf("SEARCH [%d] LIST: %.2lfms\n", num_ele, elapsed);

  /* CLOSING STUFF */
  fclose(stream);
  fclose(output);

  return 0;
}
