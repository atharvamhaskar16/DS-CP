#ifndef BST_H
#define BST_H

#include "ev.h"
typedef struct BSTNode {
    EV *ev;
    struct BSTNode *left, *right;
} BSTNode;

BSTNode* bst_insert(BSTNode *root, EV *ev);
void bst_inorder(BSTNode *root);
void bst_filter_below(BSTNode *root, int threshold);

#endif
