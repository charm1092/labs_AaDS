// 1 - ВО ВСЕХ УЗЛАХ РАЗНЫЕ ЗНАЧЕНИЯ
// 2 - ВО ВСЕХ ЛЕВЫХ ПОДДЕРЕВАХ ЗНАЧЕНИЯ МЕНЬШЕ, ЧЕМ В КОРНЕ, ВО ВСЕХ ПРАВЫХ ПОДДЕРЕВАХ БОЛЬШЕ, ЧЕМ В КОРНЕ


#ifndef __NODE__
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *l;
    struct Node *r;
} Node;

Node *CreateNode(int value) {
    Node *buffer = (Node *)malloc(sizeof(Node));
    if (buffer == NULL) {
        exit(-1);
    }

    buffer->value = value;
    buffer->r = NULL;
    buffer->l = NULL;
    return buffer;
}

// Бинарное дерево поиска

Node **FindNode(Node **root, int value) {
    Node **current = root;

    while (*current != NULL) {
        if ((*current)->value > value) {
            current = &(*current)->l;
        } else if ((*current)->value < value) {
            current = &(*current)->r;
        } else {
            break;
        }
    }

    return current;
}

void DeleteNode(Node **root) {
    if ((*root)->l == NULL && (*root)->r == NULL) {
        Node *buffer = *root;
        *root = NULL;
        free(buffer);
    } else if ((*root)->l == NULL) {
        Node *buffer = *root;
        *root = (*root)->r;
        free(buffer);
    } else if ((*root)->r == NULL) {
        Node *buffer = *root;
        *root = (*root)->l;
        free(buffer);
    } else {
        Node **current = &(*root)->r;
        while ((*current)->l != NULL) {
            current = &(*current)->l;
        }

        (*root)->value = (*current)->value;

        DeleteNode(current);
    }
}

bool TreeSearch(Node *root, int value) {
    return FindNode(&root, value) != NULL;
}

bool TreePush(Node **root, int value) {
    Node **buffer = FindNode(root, value);
    if (*buffer != NULL) {
        return false;
    }

    *buffer = CreateNode(value);
    return true;
}

bool TreePop(Node **root, int value) {
    Node **buffer = FindNode(root, value);
    if (*buffer == NULL) {
        return false;
    }

    DeleteNode(buffer);

    return true;
}

void TreeDestroy(Node **root) {
    if (*root == NULL) {
        return;
    }

    TreeDestroy(&(*root)->l);
    TreeDestroy(&(*root)->r);
    Node *buffer = *root;
    *root = NULL;
    free(buffer);
}

void PrintTree(Node *root, int level) {
    if (root == NULL) {
        return;
    }

    PrintTree(root->r, level+1); // ДЛЯ ДЕРЕВА ОБЩЕГО ВИДА ПЕРЕНОСИМ ЭТУ СТРОЧКУ ПОСЛЕ PrintTree(root->l, level+1)
    for (int i = 0; i < level; i++) {
        printf("\t");
    }
    printf("%d\n", root->value);
    PrintTree(root->l, level+1);
}

bool isBTree(Node *root) {
    if (root == NULL) {
        return true;
    }

    // если только один ребёнок
    if ((root->l == NULL && root->r != NULL) ||
        (root->l != NULL && root->r == NULL)) {
        return false;
    }

    return isBTree(root->l) && isBTree(root->r);
}

#endif