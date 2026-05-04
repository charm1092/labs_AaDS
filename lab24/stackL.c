#include "stackL.h"
#include <stdlib.h>
#include <stdio.h>

StackL *CreateStackL(){
    StackL *st = (StackL *)malloc(sizeof(StackL));
    if (st == NULL){
        exit(-1);
    }

    st->head = NULL;
    st->size = 0;
    return st;
}

bool StackLIsEmpty(StackL *st){
    return st->size == 0;
}

void StackLPush(StackL *st, Lexemme lex){
    NodeL *newNode = (NodeL *)malloc(sizeof(NodeL));
    if (newNode == NULL){
        exit(-1);
    }
    newNode->lex = lex;
    newNode->next = st->head;
    st->head = newNode;
    st->size ++;
}

void StackLPop(StackL *st){
    if (st->size == 0){
        return;
    }

    NodeL *buffer = st->head;
    st->head = st->head->next;
    free(buffer);
    st->size --;
}

Lexemme StackLPeek(StackL *st){
    if (st->size == 0){
        perror("Нельзя посмотреть элемент с вершины пустого стека\n");
        return Error();
    }
    return st->head->lex;
}

void DeleteStackL(StackL **st){
    while (!StackLIsEmpty(*st)){
        StackLPop(*st);
    }
    free(*st);
    *st = NULL;
}