#include <stdio.h>
#include <stdlib.h>
#include "BST.h"

int main() {
    Node* root = NULL;
    int command, value;

    while (1) {
        printf("\n====== МЕНЮ ======\n");
        printf("1 - Вывести дерево\n");
        printf("2 - Проверить пустое ли дерево\n");
        printf("3 - Добавить элемент\n");
        printf("4 - Удалить элемент\n");
        printf("5 - Поиск элемента\n");
        printf("6 - Очистить дерево\n");
        printf("7 - Проверка B-дерева\n");
        printf("0 - Выход\n");
        printf("Выбор: ");

        if (scanf("%d", &command) != 1) {
            printf("Ошибка ввода\n");
            break;
        }

        switch (command) {
            case 1:
                if (IsEmpty(&root)) {
                    printf("Дерево пустое\n");
                } else {
                    printf("\nДерево:\n");
                    BSTPrint(root, 0);
                }
                break;

            case 2:
                if (IsEmpty(&root)) {
                    printf("Дерево пустое\n");
                } else {
                    printf("Дерево не пустое\n");
                }
                break;

            case 3:
                printf("Введите значение: ");
                scanf("%d", &value);
                if (BSTPush(&root, value)) {
                    printf("Добавлено: %d\n", value);
                } else {
                    printf("Элемент уже существует\n");
                }
                break;

            case 4:
                printf("Введите значение: ");
                scanf("%d", &value);
                if (BSTPop(&root, value)) {
                    printf("Удалено: %d\n", value);
                } else {
                    printf("Элемент не найден\n");
                }
                break;

            case 5:
                printf("Введите значение: ");
                scanf("%d", &value);
                if (BSTSearch(root, value)) {
                    printf("Найдено\n");
                } else {
                    printf("Не найдено\n");
                }
                break;

            case 6:
                BSTDestroy(&root);
                printf("Дерево очищено\n");
                break;

            case 7:
                if (isBTree(root)) {
                    printf("Это B-дерево\n");
                } else {
                    printf("Это НЕ B-дерево\n");
                }
                break;

            case 0:
                BSTDestroy(&root);
                return 0;

            default:
                printf("Неверный ввод\n");
        }
    }

    BSTDestroy(&root);
    return 0;
}