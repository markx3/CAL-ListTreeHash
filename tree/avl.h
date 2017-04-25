#ifndef _AVL_H
#define _AVL_H
#define ELE_CHAR 80

typedef struct {
  int index;
  char *p;
  char *s;
} element_t;

typedef struct avl_node {
  struct avl_node *left;
  struct avl_node *right;
  char *key;
  element_t *element;
} avl_node_t;

typedef struct {
  avl_node_t *root;
} avl_tree_t;

avl_tree_t *avl_tree_init();
avl_node_t *avl_node_init();
element_t *element_init(int index, char *p, char *s);
int avl_node_height(avl_node_t *node);
int avl_balance_factor( avl_node_t *node );
avl_node_t *avl_rotate_leftleft( avl_node_t *node );
avl_node_t *avl_rotate_leftright( avl_node_t *node );
avl_node_t *avl_rotate_rightleft( avl_node_t *node );
avl_node_t *avl_rotate_rightright( avl_node_t *node );
avl_node_t *avl_balance_node( avl_node_t *node );
void avl_balance( avl_tree_t *tree );
void avl_insert( avl_tree_t *tree, char *value, element_t *payload);
avl_node_t *avl_find( avl_tree_t *tree, char *value );
char *calc_key(char *p, char *s);

#endif /* _AVL_H */
