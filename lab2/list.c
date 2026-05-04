#include "list.h"
#include <stdlib.h>

static void GrowPool(List *lst) {
    size_t old_capacity = lst->capacity;
    size_t new_capacity = (old_capacity < 10) ? 10 : old_capacity * 2;

    Node *buffer = (Node *)realloc(lst->data, new_capacity * sizeof(Node));
    if (buffer == NULL) {
        exit(-1);
    }

    lst->data = buffer;

    for (size_t i = old_capacity; i + 1 < new_capacity; ++i) {
        lst->data[i].next = (int)(i + 1);
    }
    lst->data[new_capacity - 1].next = lst->top;
    lst->top = (int)old_capacity;
    lst->capacity = new_capacity;
}

static int TakeFreeNode(List *lst) {
    if (lst->top == NULL_INDEX) {
        GrowPool(lst);
    }

    int index = lst->top;
    lst->top = lst->data[index].next;
    return index;
}

static void ReturnNodeToPool(List *lst, int index) {
    lst->data[index].next = lst->top;
    lst->top = index;
}

void CreateList(List *lst) {
    if (lst == NULL) {
        exit(-1);
    }

    lst->data = (Node *)malloc(INITIAL_CAPACITY * sizeof(Node));
    if (lst->data == NULL) {
        exit(-1);
    }

    lst->size = 0;
    lst->capacity = INITIAL_CAPACITY;

    lst->data[TERMINATOR_INDEX].next = TERMINATOR_INDEX;

    for (int i = 1; i < INITIAL_CAPACITY - 1; ++i) {
        lst->data[i].next = i + 1;
    }
    lst->data[INITIAL_CAPACITY - 1].next = NULL_INDEX;
    lst->top = 1;
}

bool ListIsEmpty(List *lst) {
    return lst->size == 0;
}

size_t SizeOfList(List *lst) {
    return lst->size;
}

Iterator ListBegin(List *lst) {
    return (Iterator){lst->data[TERMINATOR_INDEX].next, lst};
}

bool IteratorIsTerminator(Iterator iter) {
    return iter.node == TERMINATOR_INDEX;
}

Iterator IteratorGetNext(Iterator iter) {
    if (IteratorIsTerminator(iter)) {
        return iter;
    }

    return (Iterator){iter.list->data[iter.node].next, iter.list};
}

void IteratorMoveNext(Iterator *iter) {
    if (!IteratorIsTerminator(*iter)) {
        iter->node = iter->list->data[iter->node].next;
    }
}

int IteratorGetValue(Iterator iter) {
    if (IteratorIsTerminator(iter)) {
        return -1;
    }

    return iter.list->data[iter.node].value;
}

void IteratorSetValue(Iterator iter, int value) {
    if (!IteratorIsTerminator(iter)) {
        iter.list->data[iter.node].value = value;
    }
}

void InsertAfter(Iterator iter, int value) {
    if (IteratorIsTerminator(iter)) {
        return;
    }

    int new_node = TakeFreeNode(iter.list);
    iter.list->data[new_node].value = value;
    iter.list->data[new_node].next = iter.list->data[iter.node].next;
    iter.list->data[iter.node].next = new_node;
    iter.list->size++;
}

void InsertBegin(List *lst, int value) {
    if (lst == NULL) {
        return;
    }

    int new_node = TakeFreeNode(lst);
    lst->data[new_node].value = value;
    lst->data[new_node].next = lst->data[TERMINATOR_INDEX].next;
    lst->data[TERMINATOR_INDEX].next = new_node;
    lst->size++;
}

void IteratorDeleteNext(Iterator iter) {
    if (IteratorIsTerminator(iter)) {
        return;
    }

    int delete_node = iter.list->data[iter.node].next;
    if (delete_node == TERMINATOR_INDEX) {
        return;
    }

    iter.list->data[iter.node].next = iter.list->data[delete_node].next;
    ReturnNodeToPool(iter.list, delete_node);
    iter.list->size--;
}

void ListDeleteBegin(List *lst) {
    if (lst == NULL || ListIsEmpty(lst)) {
        return;
    }

    int delete_node = lst->data[TERMINATOR_INDEX].next;
    lst->data[TERMINATOR_INDEX].next = lst->data[delete_node].next;
    ReturnNodeToPool(lst, delete_node);
    lst->size--;
}

void ListDestroy(List *lst) {
    if (lst == NULL) {
        return;
    }

    free(lst->data);
    lst->data = NULL;
    lst->size = 0;
    lst->capacity = 0;
    lst->top = NULL_INDEX;
}

void ReplaceTwoHalsOfList(List *lst) {
    if (lst == NULL || lst->size < 2) {
        return;
    }

    int *values = (int *)malloc(lst->size * sizeof(int));
    int *result = (int *)malloc(lst->size * sizeof(int));
    if (values == NULL || result == NULL) {
        free(values);
        free(result);
        exit(-1);
    }

    size_t count = 0;
    Iterator it = ListBegin(lst);
    while (!IteratorIsTerminator(it) && count < lst->size) {
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

    it = ListBegin(lst);
    size_t i = 0;
    while (!IteratorIsTerminator(it) && i < count) {
        IteratorSetValue(it, result[i]);
        IteratorMoveNext(&it);
        ++i;
    }

    free(values);
    free(result);
}