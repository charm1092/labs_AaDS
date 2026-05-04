#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>
#include <stddef.h>

#define INITIAL_CAPACITY 10

typedef struct {
    int key;
    char value[50];
} data_type;

typedef struct {
    data_type *data;
    size_t size;
    size_t capacity;
} Stack;

typedef struct {
    Stack *s;
    int current_idx;
} Iterator;

void createStack(Stack *s);
bool isEmpty(const Stack *s);
void stackPushBack(Stack *s, data_type value);
data_type stackPopBack(Stack *s);
void printStack(const Stack *s);
size_t sizeStack(const Stack *s);
void insertionSort(Stack *s);
void Insert(Stack *s, data_type value);
void Destroy(Stack *s);
#endif