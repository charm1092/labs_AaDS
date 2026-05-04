#ifndef __stackT_h__
#define __stackT_h__

#include <stdbool.h>
#include <stddef.h>

typedef struct NodeT NodeT;
typedef struct NodeNT NodeNT;

struct NodeT {
    NodeNT *node;
    NodeT *next;
};

typedef struct StackT {
    NodeT *head;
    size_t size;
} StackT;

StackT *CreateStackT();
bool StackTIsEmpty(StackT *st);
void StackTPush(StackT *st, NodeNT *node);
void StackTPop(StackT *st);
NodeNT *StackTPeek(StackT *st);
void DeleteStackT(StackT **st);

#endif