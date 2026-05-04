#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "BST.h"

Node** BSTFindNode(Node **root, int value) {
    Node** current = root;
    while (*current != NULL) {
        if ((*current)->value > value) {
            current = &(*current)->left;
        } else if ((*current)->value < value) {
            current = &(*current)->right;
        } else {
            break;
        }
    } return current;
} 

bool BSTSearch(Node* root, int value){
    return *BSTFindNode(&root, value) != NULL;
}

bool BSTPush(Node **root, int value){
    Node **current = BSTFindNode(root, value);
    if (*current != NULL) {
        return false;
    }
    *current = (Node*)malloc(sizeof(Node));
    if ((*current) == NULL){
        exit(-1);
    }
    (*current)->left = NULL;
    (*current)->right = NULL;
    (*current)->value = value;


    return true;
}

void BSTPrint(Node* root, int tabs) {
    if (root == NULL) {
        return;
    } 
    BSTPrint(root->right, tabs + 1);
    for (int i = 0; i < tabs; i++) {
        printf("    ");
    }

    printf("%d\n", root->value);

    BSTPrint(root->left, tabs + 1);
}

void BSTDeleteNode(Node** root) {
    if ((*root)->left == NULL && (*root)->right == NULL) {
        free(*root);
        *root = NULL;
    } else if ((*root)->left == NULL) {
        Node* buffer = (*root);
        *root = (*root)->right;
        free(buffer);
    } else if ((*root)->right == NULL) {
        Node* buffer = (*root);
        *root = (*root)->left;
        free(buffer);
    } else {
        Node** current = &(*root)->right;
        while (((*current)->left) != NULL) {
            current = &(*current)->left;
        }
        (*root)->value = (*current)->value;
        BSTDeleteNode(current);
    }
}

void BSTDestroy(Node** root) {
    if (*root == NULL) {
        return;
    }
    BSTDestroy(&(*root)->right);
    BSTDestroy(&(*root)->left);
    free(*root);
    *root = NULL;
}

bool BSTPop(Node** root, int value) {
    Node** current = BSTFindNode(root, value);
    if (*current == NULL) {
        return false;
    }
    BSTDeleteNode(current);
    return true;
}

bool IsEmpty(Node** root) {
    return *root == NULL;
}

bool isBTree(Node *root) {
    if (root == NULL) {
        return true;
    }

    if ((root->left == NULL && root->right != NULL) ||
        (root->left != NULL && root->right == NULL)) {
        return false;
    }

    return isBTree(root->left) && isBTree(root->right);
}
