#ifndef __BST__
#define __BST__ 
#include <stdbool.h>

typedef struct Node Node;
struct Node {
    int value;
    Node* left;
    Node* right;
};

bool BSTSearch(Node *root, int value);
bool BSTPop(Node **root, int value);
bool BSTPush(Node **root, int value);
bool IsEmpty(Node **root);
void BSTPrint(Node *root, int tabs);
void BSTDestroy(Node **root);
void BSTDeleteNode(Node** root);
Node** BSTFindNode(Node **root, int value); 
int BSTDepth(Node* root);

#endif 
