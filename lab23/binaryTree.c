#include<stdlib.h>
#include"binaryTree.h"

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* insert(Node *node, int data) {
    if (node == NULL) {
        return createNode(data);
    }
    
    if (data < node->data) {
        node->left = insert(node->left, data);
    } else if(data > node->data) {
        node->right = insert(node->right, data);
    }
    
    return node;
}

int main() {

}