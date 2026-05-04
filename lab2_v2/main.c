#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(void) {
    List *l = NULL;
    int created = 0;
    int choice;

    while (1) {
        printf("\nМеню:\n");
        printf("1. Создать список\n");
        printf("2. Добавить элемент\n");
        printf("3. Удалить элемент\n");
        printf("4. Вывести список\n");
        printf("5. Длина списка\n");
        printf("6. Поменять половины списка\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода.\n");
            break;
        }

        switch (choice) {

            case 1:
                if (created) {
                    printf("Список уже создан.\n");
                } else {
                    l = ListCreate();
                    created = 1;
                    printf("Список успешно создан.\n");
                }
                break;

            case 2: {
                if (!created) {
                    printf("Список не создан.\n");
                    break;
                }

                int where;
                int val;
                printf("Введите значение: ");
                scanf("%d", &val);

                printf("Вставка: в начало (0) или после индекса (1): ");
                scanf("%d", &where);
                

                if (where == 0) {
                    InsertBegin(l, val);
                } else {
                    int index;
                    printf("Введите индекс: ");
                    scanf("%d", &index);

                    if (index < 0 || index >= (int)ListSize(l)) {
                        printf("Некорректный индекс.\n");
                        break;
                    }

                    Iterator it = ListBegin(l);
                    for (int i = 0; i < index; i++) {
                        IteratorMoveNext(&it);
                    }

                    InsertAfter(&it, val);
                }

                PrintList(l);
                break;
            }

            case 3: {
                if (!created || ListIsEmpty(l)) {
                    printf("Список пуст или не создан.\n");
                    break;
                }

                int index;
                printf("Введите индекс элемента: ");
                scanf("%d", &index);

                if (index < 0 || index >= (int)ListSize(l)) {
                    printf("Некорректный индекс.\n");
                    break;
                }

                if (index == 0) {
                    ListDeleteBegin(l);
                } else {
                    Iterator it = ListBegin(l);
                    for (int i = 0; i < index - 1; i++) {
                        IteratorMoveNext(&it);
                    }

                    IteratorDeleteNext(it);
                }

                printf("Элемент удалён.\n");
                PrintList(l);
                break;
            }

            case 4:
                if (!created) {
                    printf("Список не создан.\n");
                } else {
                    PrintList(l);
                }
                break;

            case 5:
                if (!created) {
                    printf("Список не создан.\n");
                } else {
                    printf("Длина списка: %zu\n", ListSize(l));
                }
                break;

            case 6:
                if (!created) {
                    printf("Список не создан.\n");
                } else {
                    Swap(l);
                    printf("Половины списка переставлены.\n");
                    PrintList(l);
                }
                break;

            case 0:
                if (l) ListDestroy(&l);
                return 0;

            default:
                printf("Ошибка! Нет такого варианта выбора.\n");
        }
    }

    if (l) ListDestroy(&l);
    return 0;
}