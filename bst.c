#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BSTNode* bst_insert(BSTNode *root, EV *ev) {
    if (!root) {
        BSTNode *n = (BSTNode*)malloc(sizeof(BSTNode));
        n->ev = ev; n->left = n->right = NULL;
        return n;
    }
    if (ev->battery < root->ev->battery) root->left = bst_insert(root->left, ev);
    else root->right = bst_insert(root->right, ev);
    return root;
}

void bst_inorder(BSTNode *root) {
    if (!root) return;
    bst_inorder(root->left);
    printf("[%s|%d%%] ", root->ev->id, root->ev->battery);
    bst_inorder(root->right);
}

void bst_filter_below(BSTNode *root, int threshold) {
    if (!root) return;
    bst_filter_below(root->left, threshold);
    if (root->ev->battery < threshold) {
        printf("  - %s battery=%d%% type=%s arrival=%d\n",
               root->ev->id, root->ev->battery,
               root->ev->userType ? "Premium":"Normal", root->ev->arrivalTime);
    }
    bst_filter_below(root->right, threshold);
}
