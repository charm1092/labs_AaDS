#ifndef __LIST__
#define __LIST__

#include <stdbool.h>
#include <stddef.h>

#define INITIAL_CAPACITY 10
#define TERMINATOR_INDEX 0 // конец основого списка
#define NULL_INDEX ((size_t)-1) // конец списка свободных узлов

typedef int CountType;

typedef struct Node {
    CountType data;
    size_t next;
} Node;

typedef struct List {
    Node *nodes;
    size_t size;
    size_t capacity;
    size_t free; // индекс первого свободного узла(индекса) в массиве узлов
} List;

typedef struct Iterator {
    List *l;
    size_t current;
} Iterator;

List *ListCreate();
bool ListIsEmpty(List *l);
size_t ListSize(List *l);

Iterator ListBegin(List *l);
Iterator ListEnd(List *l);
bool IteratorIsTerminator(Iterator iter);
void IteratorMoveNext(Iterator *iter);
CountType IteratorGetValue(Iterator iter);
void IteratorSetValue(Iterator *iter, CountType value);

void InsertAfter(Iterator *iter, CountType value);
void InsertBegin(List *l, CountType value);
void IteratorDeleteNext(Iterator iter);
void ListDeleteBegin(List *l);
void ListDestroy(List **l);
void PrintList(List *l);
void Swap(List *l);

#endif