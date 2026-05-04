#include<stdio.h>
#include<stdlib.h>
#include"stack.h"

static void GrowPool(Stack *s) {
    size_t old_capacity = s->capacity;
    size_t new_capacity = (old_capacity < INITIAL_CAPACITY) ? INITIAL_CAPACITY : old_capacity * 2;

    data_type *buffer = (data_type *)realloc(s->data, new_capacity * sizeof(data_type));
    
    if (buffer == NULL) {
        exit(-1); 
    }

    s->data = buffer;
    s->capacity = new_capacity;
}

void createStack(Stack *s) {
    s->data = malloc(INITIAL_CAPACITY * sizeof(data_type));
    s->size = 0;
    s->capacity = INITIAL_CAPACITY;
}

bool isEmpty(const Stack *s) {
    return s->size == 0;
}

void stackPushBack(Stack *s, data_type value) {
    if (s->size == s->capacity) {
        GrowPool(s);
    }

    s->data[s->size] = value;
    s->size++;
}

data_type stackPopBack(Stack *s) {
    if (isEmpty(s)) {
        exit(-1);
    }

    s->size--;
    return s->data[s->size];
}

data_type stackTop(const Stack *s) {
    if (isEmpty(s)) {
        exit(-1);
    }

    return s->data[s->size - 1];
}

void printStack(const Stack *s) {
    for (int i = (int)s->size - 1; i >= 0; i--) {
        printf("%d %s\n", s->data[i].key, s->data[i].value);
    }
}

size_t sizeStack(const Stack *s) {
    return s->size;
}

void insertionSort(Stack *s) {
    Stack temp;
    createStack(&temp);

    while (!isEmpty(s)) {
        Insert(&temp, stackPopBack(s));
    }

    free(s->data);
    *s = temp;
}

void Insert(Stack *s, data_type value) {
    Stack temp;
    createStack(&temp);

    while (!isEmpty(s) && stackTop(s).key < value.key) {
        stackPushBack(&temp, stackPopBack(s));
    }

    stackPushBack(s, value);

    while (!isEmpty(&temp)) {
        stackPushBack(s, stackPopBack(&temp));
    }

    Destroy(&temp);
}

void Destroy(Stack *s) {
    free(s->data);
    s->data = NULL;
    s->size = 0;
    s->capacity = 0;
}