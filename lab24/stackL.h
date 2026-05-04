#ifndef __stackL_h__
#define __stackL_h__
#include <stdbool.h>
#include "lexemme.h"
#include <stddef.h>

typedef struct NodeL NodeL;

struct NodeL{
    Lexemme lex;
    NodeL *next;
};

typedef struct StackL{
    NodeL *head;
    size_t size;
}StackL;

StackL *CreateStackL();
bool StackLIsEmpty(StackL *st);
void StackLPush(StackL *st, Lexemme lex);
void StackLPop(StackL *st);
Lexemme StackLPeek(StackL *st);
void DeleteStackL(StackL **st);

#endif