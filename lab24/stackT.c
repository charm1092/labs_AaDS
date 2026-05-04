#include "stackT.h"
#include <stdlib.h>
#include <stdio.h>

StackT *CreateStackT() {
    StackT *st = (StackT *)malloc(sizeof(StackT));
    if (st == NULL){
        exit(-1);
    }
    st->head = NULL;
    st->size = 0;
    return st;
}

bool StackTIsEmpty(StackT *st) {
    return st->size == 0;
}

void StackTPush(StackT *st, NodeNT *node) {
    NodeT *newNode = (NodeT *)malloc(sizeof(NodeT));
    if (newNode == NULL){
        exit(-1);
    }
    newNode->node = node;
    newNode->next = st->head;
    st->head = newNode;
    st->size++;
}

void StackTPop(StackT *st) {
    if (st->size == 0){
        return;
    }
    NodeT *buffer = st->head;
    st->head = st->head->next;
    free(buffer);
    st->size--;
}

NodeNT *StackTPeek(StackT *st) {
    if (st->size == 0){
        perror("Пустой стек\n");
        return NULL;
    }
    return st->head->node;
}

void DeleteStackT(StackT **st) {
    while (!StackTIsEmpty(*st)) {
        StackTPop(*st);
    }
    free(*st);
    *st = NULL;
}