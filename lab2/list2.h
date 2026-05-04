#ifndef __LIST__
#define __LIST__

#include <stddef.h>
#include <stdbool.h>

#define INITIAL_POOL_SIZE 100
#define NULL_INDEX (-1)

typedef struct Node Node;
typedef struct List List;
typedef struct Iterator Iterator;

struct Node {
    int value;
    int next;   
};

struct List {
    Node *data;     
    size_t size;   
    size_t capacity; 

    int head;  
    int top;    
};

struct Iterator {
    int node;   
    List *list;
};

void CreateList(List *lst);
bool ListIsEmpty(List *lst);
size_t SizeOfList(List *lst);
Iterator ListBegin(List *lst);
Iterator IteratorGetNext(Iterator iter);
void IteratorMoveNext(Iterator *iter);
int IteratorGetValue(Iterator iter);
void IteratorSetValue(Iterator iter, int value);
bool IteratorIsTerminator(Iterator iter);
void InsertAfter(Iterator iter, int value);
void InsertBegin(List *lst, int value);
void IteratorDeleteNext(Iterator iter);
void ListDeleteBegin(List *lst);
void ListDestroy(List *lst);
void ReplaceTwoHalsOfList(List *lst);

#endif