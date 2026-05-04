#ifndef __TREE__
#define __TREE__

typedef struct Node Node;

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

Node* createNode(int data);
Node* insert(Node *node, int data);
void printTree();

#endif