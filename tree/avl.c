#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

// IMPLEMENTATIONS BROUGHT BY https://gist.github.com/tonious/1377768

// Initializes AVL Tree.
avl_tree_t *avl_tree_init() {
  avl_tree_t *t = NULL;
  if ( (t = malloc(sizeof(avl_tree_t))) == NULL)
    return NULL;
  t->root = NULL;
  return t;
}

// Initializes AVL Tree's node.
avl_node_t *avl_node_init() {
  avl_node_t *node = NULL;
  if ( (node = malloc(sizeof(avl_node_t))) == NULL)
    return NULL;
  node->left = NULL;
  node->right = NULL;
  node->key = malloc(sizeof(char)*ELE_CHAR*2);
  node->element = NULL;
  return node;
}

element_t *element_init(int index, char *p, char *s) {
  element_t *ele = NULL;
  if ( (ele = malloc(sizeof(element_t))) == NULL)
    return NULL;
  ele->index = index;
  ele->p = malloc(sizeof(char)*ELE_CHAR);
  strcpy(ele->p, p);
  ele->s = malloc(sizeof(char)*ELE_CHAR);
  strcpy(ele->s, s);
  return ele;
}

int avl_node_height(avl_node_t *node) {
  int height_left = 0;
	int height_right = 0;

	if( node->left ) height_left = avl_node_height( node->left );
	if( node->right ) height_right = avl_node_height( node->right );

return height_right > height_left ? ++height_right : ++height_left;
}

int avl_balance_factor( avl_node_t *node ) {
	int bf = 0;

	if( node->left  ) bf += avl_node_height( node->left );
	if( node->right ) bf -= avl_node_height( node->right );

	return bf ;
}

avl_node_t *avl_rotate_leftleft( avl_node_t *node ) {
 	avl_node_t *a = node;
	avl_node_t *b = a->left;

	a->left = b->right;
	b->right = a;

	return( b );
}

avl_node_t *avl_rotate_leftright( avl_node_t *node ) {
	avl_node_t *a = node;
	avl_node_t *b = a->left;
	avl_node_t *c = b->right;

	a->left = c->right;
	b->right = c->left;
	c->left = b;
	c->right = a;

	return( c );
}

avl_node_t *avl_rotate_rightleft( avl_node_t *node ) {
	avl_node_t *a = node;
	avl_node_t *b = a->right;
	avl_node_t *c = b->left;

	a->right = c->left;
	b->left = c->right;
	c->right = b;
	c->left = a;

	return( c );
}

/* Right Right Rotate */
avl_node_t *avl_rotate_rightright( avl_node_t *node ) {
	avl_node_t *a = node;
	avl_node_t *b = a->right;

	a->right = b->left;
	b->left = a;

	return( b );
}

avl_node_t *avl_balance_node( avl_node_t *node ) {
	avl_node_t *newroot = NULL;

	/* Balance our children, if they exist. */
	if( node->left )
		node->left  = avl_balance_node( node->left  );
	if( node->right )
		node->right = avl_balance_node( node->right );

	int bf = avl_balance_factor( node );

	if( bf >= 2 ) {
		/* Left Heavy */

		if( avl_balance_factor( node->left ) <= -1 )
			newroot = avl_rotate_leftright( node );
		else
			newroot = avl_rotate_leftleft( node );

	} else if( bf <= -2 ) {
		/* Right Heavy */

		if( avl_balance_factor( node->right ) >= 1 )
			newroot = avl_rotate_rightleft( node );
		else
			newroot = avl_rotate_rightright( node );

	} else {
		/* This node is balanced -- no change. */

		newroot = node;
	}

	return( newroot );
}

void avl_balance( avl_tree_t *tree ) {

	avl_node_t *newroot = NULL;

	newroot = avl_balance_node( tree->root );

	if( newroot != tree->root )  {
		tree->root = newroot;
	}
}


void avl_insert( avl_tree_t *tree, char *value, element_t *payload) {
	avl_node_t *node = NULL;
	avl_node_t *next = NULL;
	avl_node_t *last = NULL;

	/* Well, there must be a first case */
	if( tree->root == NULL ) {
		node = avl_node_init();
		//node->key = value;
    strcpy(node->key, value);
    node->element = payload;

		tree->root = node;

	/* Okay.  We have a root already.  Where do we put this? */
	} else {
		next = tree->root;

		while( next != NULL ) {
			last = next;

			if( strcmp(value, next->key) < 0) {
				next = next->left;

			} else if( strcmp(value, next->key) > 0) {
				next = next->right;

			/* Have we already inserted this node? */
    } else if( strcmp(value, next->key) == 0) {
				/* This shouldn't happen. */
			}
		}

		node = avl_node_init();
    strcpy(node->key, value);
    node->element = payload;

		if( strcmp(value, last->key) < 0 ) last->left = node;
		if( strcmp(value, last->key) > 0 ) last->right = node;

	}

	avl_balance( tree );
}

avl_node_t *avl_find( avl_tree_t *tree, char *value ) {
	avl_node_t *current = tree->root;

	while( current && strcmp(value, current->key) != 0 ) {
		if(strcmp(value, current->key) > 0)
			current = current->right;
		else
			current = current->left;
	}

	return current;
}
