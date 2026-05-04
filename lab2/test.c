#include <stdio.h>
#include "list.h"

void printList(List *list) {
    Iterator it = ListBegin(list);
    printf("Список: ");

    while (!IteratorIsTerminator(it)) {
        printf("%d ", IteratorGetValue(it));
        IteratorMoveNext(&it);
    }

    printf("\n");
}

int main(void) {
    List list;
    CreateList(&list);

    int choice;
    int value;
    int index;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Вставить в начало\n");
        printf("2. Вставить после индекса\n");
        printf("3. Удалить первый элемент\n");
        printf("4. Удалить элемент после индекса\n");
        printf("5. Вывести список\n");
        printf("6. Длина списка\n");
        printf("7. Поменять местами две половины списка\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Введите значение: ");
                if (scanf("%d", &value) != 1) {
                    printf("Ошибка ввода.\n");
                    ListDestroy(&list);
                    return 1;
                }
                InsertBegin(&list, value);
                break;

            case 2: {
                if (ListIsEmpty(&list)) {
                    printf("Список пуст.\n");
                    break;
                }

                printf("Введите индекс и значение: ");
                if (scanf("%d %d", &index, &value) != 2) {
                    printf("Ошибка ввода.\n");
                    ListDestroy(&list);
                    return 1;
                }

                if (index < 0 || index >= (int)SizeOfList(&list)) {
                    printf("Некорректный индекс.\n");
                    break;
                }

                Iterator it = ListBegin(&list);
                for (int i = 0; i < index; i++) {
                    IteratorMoveNext(&it);
                }

                InsertAfter(it, value);
                break;
            }

            case 3:
                ListDeleteBegin(&list);
                break;

            case 4: {
                if (ListIsEmpty(&list) || SizeOfList(&list) < 2) {
                    printf("Недостаточно элементов для удаления следующего.\n");
                    break;
                }

                printf("Введите индекс: ");
                if (scanf("%d", &index) != 1) {
                    printf("Ошибка ввода.\n");
                    ListDestroy(&list);
                    return 1;
                }

                if (index < 0 || index >= (int)SizeOfList(&list) - 1) {
                    printf("Некорректный индекс. Для удаления следующего элемента нужен индекс от 0 до %zu.\n", SizeOfList(&list) - 2);
                    break;
                }

                Iterator it = ListBegin(&list);
                for (int i = 0; i < index; i++) {
                    IteratorMoveNext(&it);
                }

                IteratorDeleteNext(it);
                printf("Следующий элемент удалён.\n");
                break;
            }

            case 5:
                printList(&list);
                break;

            case 6:
                printf("Длина списка: %zu\n", SizeOfList(&list));
                break;

            case 7:
                ReplaceTwoHalsOfList(&list);
                printf("Половины списка переставлены.\n");
                break;

            case 0:
                ListDestroy(&list);
                return 0;

            default:
                printf("Ошибка! Нет такого варианта выбора.\n");
        }
    }

    ListDestroy(&list);
    return 0;
}