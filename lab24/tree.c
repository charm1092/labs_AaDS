#include "tree.h"
#include <stdlib.h>
#include <stdio.h>
#include "stackL.h"
#include "stackT.h"

NodeNT *CreateNodeNT(Lexemme lex){
    NodeNT *node = (NodeNT *)malloc(sizeof(NodeNT));
    if (node == NULL){
        exit(-1);
    }

    node->lex = lex;
    node->child = NULL;
    node->brother = NULL;
    return node;
}

void AddChild(NodeNT *parent, NodeNT *newChild){
    if (parent->child == NULL){
        parent->child = newChild;
    }
    else{
        NodeNT *current = parent->child;
        while (current->brother != NULL){
            current = current->brother;
        }
        current->brother = newChild;
    }
}

void PrintNTree(NodeNT *root, int level){
    if (root == NULL){
        return;
    }

    for (int i = 0; i < level; ++i){
        printf("\t");
    }

    PrintLexemme(root->lex, false);
    printf("\n");

    PrintNTree(root->child, level + 1);
    PrintNTree(root->brother, level);
}

void DestroyNTree(NodeNT **root){
    if (*root == NULL){
        return;
    }

    DestroyNTree(&(*root)->child);
    DestroyNTree(&(*root)->brother);

    free(*root);
    *root = NULL;
}



NodeNT* buildTree(StackL *postfix) {
    if (postfix == NULL || StackLIsEmpty(postfix)) {
        return NULL;
    }

    StackT *st = CreateStackT();

    while (!StackLIsEmpty(postfix)) {
        Lexemme lex = StackLPeek(postfix);
        StackLPop(postfix);

        if (lex.Type == NUMBER || lex.Type == VARIABLE) {
            NodeNT *node = CreateNodeNT(lex);
            StackTPush(st, node);
        } else if (lex.Type == PRIMITIVE_OPERATOR) {
            NodeNT *node = CreateNodeNT(lex);

            NodeNT *right = StackTPeek(st);
            StackTPop(st);

            NodeNT *left = StackTPeek(st);
            StackTPop(st);
            AddChild(node, left);
            AddChild(node, right);

            StackTPush(st, node);
        }
    }

    NodeNT *root = StackTPeek(st);
    StackTPop(st);

    DeleteStackT(&st);

    return root;
}