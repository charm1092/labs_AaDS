#include <stdio.h>
#include "stack.h"

static data_type readElement(void) {
    data_type item;

    printf("Enter key: ");
    scanf("%d", &item.key);

    printf("Enter value: ");
    scanf("%49s", item.value);

    return item;
}

int main(void) {
    Stack stack;
    createStack(&stack);

    int choice;

    do {
        printf("\n====MENU====\n");
        printf("1. Push element\n");
        printf("2. Pop element\n");
        printf("3. Print stack\n");
        printf("4. Sort stack\n");
        printf("5. Insert into sorted stack\n");
        printf("0. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                data_type item = readElement();
                stackPushBack(&stack, item);
                break;
            }
            case 2: {
                if (isEmpty(&stack)) {
                    printf("Stack is empty\n");
                } else {
                    data_type item = stackPopBack(&stack);
                    printf("Removed: %d %s\n", item.key, item.value);
                }
                break;
            }
            case 3:
                printStack(&stack);
                break;
            case 4:
                insertionSort(&stack);
                printf("Stack sorted\n");
                break;
            case 5: {
                data_type item = readElement();

                insertionSort(&stack);
                Insert(&stack, item);

                printf("Element inserted into sorted stack\n");
                break;
            }
            case 0:
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);

    Destroy(&stack);
    return 0;
}