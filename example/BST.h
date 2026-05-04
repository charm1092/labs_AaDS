#ifndef __BST__
#define __BST__

#include <stdbool.h>

typedef struct Node Node;

struct Node {
    int value;
    Node *left;
    Node *right;
};

bool BSTPush(Node **root, int value);
bool BSTPop(Node **root, int value);
bool BSTSearch(Node *root, int value);

bool IsEmpty(Node **root);
void BSTPrint(Node *root, int tabs);
void BSTDestroy(Node **root);

bool isBTree(Node *root);

#endif