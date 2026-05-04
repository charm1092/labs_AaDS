

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// объявление структуры узла (должно совпадать с example.c)
typedef struct Node {
    int value;
    struct Node *l;
    struct Node *r;
} Node;

// объявления функций из example.c
void TreePush(Node **root, int value);
void TreePop(Node **root, int value);
void PrintTree(Node *root, int level);
void TreeDestroy(Node **root);

// функция проверки B-дерева
bool isBTree(Node *root);

int main() {
    Node *root = NULL;
    int choice, value;

    while (1) {
        printf("\nМеню:\n");
        printf("1 - Добавить элемент\n");
        printf("2 - Удалить элемент\n");
        printf("3 - Вывести дерево\n");
        printf("4 - Проверить B-дерево\n");
        printf("0 - Выход\n");
        printf("Выберите действие: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Введите значение: ");
                scanf("%d", &value);
                TreePush(&root, value);
                break;

            case 2:
                printf("Введите значение: ");
                scanf("%d", &value);
                TreePop(&root, value);
                break;

            case 3:
                printf("Дерево:\n");
                PrintTree(root, 0);
                break;

            case 4:
                if (isBTree(root)) {
                    printf("Дерево является B-деревом\n");
                } else {
                    printf("Дерево НЕ является B-деревом\n");
                }
                break;

            case 0:
                TreeDestroy(&root);
                return 0;

            default:
                printf("Неверный выбор\n");
        }
    }

    TreeDestroy(&root);
    return 0;
}