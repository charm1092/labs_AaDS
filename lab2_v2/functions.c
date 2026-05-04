#include <stdio.h>
#include <stdlib.h>
#include "list.h"

static void GrowPool(List *l) {
    size_t old_capacity = l->capacity;
    size_t new_capacity = (old_capacity < INITIAL_CAPACITY) ? INITIAL_CAPACITY : old_capacity * 2;

    Node *buffer = (Node *)realloc(l->nodes, new_capacity * sizeof(Node));
    if (buffer == NULL) {
        exit(-1);
    }

    l->nodes = buffer;

    for (size_t i = old_capacity; i + 1 < new_capacity; ++i) {
        l->nodes[i].next = i + 1;
    }
    l->nodes[new_capacity - 1].next = l->free;
    l->free = old_capacity;
    l->capacity = new_capacity;
}

static size_t TakeFreeNode(List *l) {
    if (l->free == NULL_INDEX) {
        GrowPool(l);
    }

    size_t index = l->free;
    l->free = l->nodes[index].next;
    return index;
}

static void ReturnNodeToPool(List *l, size_t index) {
    l->nodes[index].next = l->free;
    l->free = index;
}

List *ListCreate(void) {
    List *l = (List *)malloc(sizeof(List));
    if (l == NULL) {
        exit(-1);
    }

    l->nodes = (Node *)malloc(INITIAL_CAPACITY * sizeof(Node));
    if (l->nodes == NULL) {
        free(l);
        exit(-1);
    }

    l->size = 0;
    l->capacity = INITIAL_CAPACITY;
    l->nodes[TERMINATOR_INDEX].next = TERMINATOR_INDEX;

    for (size_t i = 1; i < INITIAL_CAPACITY - 1; ++i) {
        l->nodes[i].next = i + 1;
    }
    l->nodes[INITIAL_CAPACITY - 1].next = NULL_INDEX;
    l->free = 1;

    return l;
}

bool ListIsEmpty(List *l) {
    return l->size == 0;
}

size_t ListSize(List *l) {
    return l->size;
}

Iterator ListBegin(List *l) {
    return (Iterator){l, l->nodes[TERMINATOR_INDEX].next};
}

Iterator ListEnd(List *l) {
    return (Iterator){l, TERMINATOR_INDEX};
}

bool IteratorIsTerminator(Iterator iter) {
    return iter.current == TERMINATOR_INDEX;
}

void IteratorMoveNext(Iterator *iter) {
    if (!IteratorIsTerminator(*iter)) {
        iter->current = iter->l->nodes[iter->current].next;
    }
}

CountType IteratorGetValue(Iterator iter) {
    if (IteratorIsTerminator(iter)) {
        return 0;
    }
    return iter.l->nodes[iter.current].data;
}

void IteratorSetValue(Iterator *iter, CountType value) {
    if (!IteratorIsTerminator(*iter)) {
        iter->l->nodes[iter->current].data = value;
    }
}

void InsertAfter(Iterator *iter, CountType value) {
    if (IteratorIsTerminator(*iter)) {
        return;
    }

    size_t new_index = TakeFreeNode(iter->l);
    iter->l->nodes[new_index].data = value;
    iter->l->nodes[new_index].next = iter->l->nodes[iter->current].next;
    iter->l->nodes[iter->current].next = new_index;
    iter->l->size++;
}

void InsertBegin(List *l, CountType value) {
    if (l == NULL) {
        return;
    }

    size_t new_index = TakeFreeNode(l);
    l->nodes[new_index].data = value;
    l->nodes[new_index].next = l->nodes[TERMINATOR_INDEX].next;
    l->nodes[TERMINATOR_INDEX].next = new_index;
    l->size++;
}

void IteratorDeleteNext(Iterator iter) {
    if (IteratorIsTerminator(iter)) {
        return;
    }

    size_t delete_index = iter.l->nodes[iter.current].next;
    if (delete_index == TERMINATOR_INDEX) {
        return;
    }

    iter.l->nodes[iter.current].next = iter.l->nodes[delete_index].next;
    ReturnNodeToPool(iter.l, delete_index);
    iter.l->size--;
}

void ListDeleteBegin(List *l) {
    if (l == NULL || ListIsEmpty(l)) {
        return;
    }

    size_t delete_index = l->nodes[TERMINATOR_INDEX].next;
    l->nodes[TERMINATOR_INDEX].next = l->nodes[delete_index].next;
    ReturnNodeToPool(l, delete_index);
    l->size--;
}

void ListDestroy(List **l) {
    if (l == NULL || *l == NULL) {
        return;
    }

    free((*l)->nodes);
    (*l)->nodes = NULL;
    free(*l);
    *l = NULL;
}

void PrintList(List *l) {
    if (l == NULL) {
        printf("List is NULL\n");
        return;
    }

    if (ListIsEmpty(l)) {
        printf("List is empty\n");
        return;
    }

    Iterator it = ListBegin(l);
    while (!IteratorIsTerminator(it)) {
        printf("%d", IteratorGetValue(it));
        IteratorMoveNext(&it);
        if (!IteratorIsTerminator(it)) {
            printf(" ");
        }
    }
    printf("\n");
}

void Swap(List *l) {
    if (l == NULL || l->size < 2) {
        return;
    }

    CountType *values = (CountType *)malloc(l->size * sizeof(CountType));
    CountType *result = (CountType *)malloc(l->size * sizeof(CountType));
    if (values == NULL || result == NULL) {
        free(values);
        free(result);
        exit(-1);
    }

    size_t count = 0;
    Iterator it = ListBegin(l);
    while (!IteratorIsTerminator(it) && count < l->size) {
        values[count++] = IteratorGetValue(it);
        IteratorMoveNext(&it);
    }

    size_t mid = count / 2;
    size_t k = 0;

    if (count % 2 == 0) {
        for (size_t i = mid; i < count; ++i) {
            result[k++] = values[i];
        }
        for (size_t i = 0; i < mid; ++i) {
            result[k++] = values[i];
        }
    } else {
        for (size_t i = mid + 1; i < count; ++i) {
            result[k++] = values[i];
        }
        result[k++] = values[mid];
        for (size_t i = 0; i < mid; ++i) {
            result[k++] = values[i];
        }
    }

    it = ListBegin(l);
    size_t i = 0;
    while (!IteratorIsTerminator(it) && i < count) {
        l->nodes[it.current].data = result[i];
        IteratorMoveNext(&it);
        ++i;
    }

    free(values);
    free(result);
}