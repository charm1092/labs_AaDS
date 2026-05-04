#include <stdio.h>
#include <stdlib.h>
#include "BST.h"
int main() 
{
    Node* root = NULL;
    
    while (1) {

        
        printf("------\nSelect the command:\n1. Print tree;\n2. Check is empty;\n3. Push number;\n4. Pop number;\n5. Search number;\n6. Destroy the tree;\n7. Depth of the treee;\n8. Exit.\nYour number is: ");
        int command;
        scanf("%d", &command);
        if (command == 1) {
            if (IsEmpty(&root)) {
                printf("Tree is empty\n");
            } else {
                printf("\n");
                BSTPrint(root, 0);
                printf("\n");
            }
        } else if (command == 2) {
            if (IsEmpty(&root)) {
                printf("Tree is empty\n");
            } else {
                printf("Tree is not empty\n");
            }
        } else if (command == 3) {
            int value;
            printf("Enter value: ");
            if (scanf("%d", &value) == EOF) {
                break;
            }
            if (BSTPush(&root, value)) {
                printf("Value %d pushed in the tree\n", value);
            } else {
                printf("Value %d already in the tree\n", value);
            }

        } else if (command == 4) {
            int value;
            printf("Enter value: ");
            if (scanf("%d", &value) == EOF) {
                break;
            }
            if (BSTPop(&root, value)) {
                printf("Value %d popped from the tree\n", value);
            } else {
                printf("Value %d was not in the tree \n", value);
            }
        } else if (command == 5) {
            int value;
            printf("Enter value: ");
            if (scanf("%d", &value) == EOF) {
                break;
            }
            if (BSTSearch(root, value)) {
                printf("Value %d is in the tree\n", value);
            } else {
                printf("Value %d is not the in tree \n", value);
            }
        } else if (command == 6) {
            if (IsEmpty(&root)) {
                printf("The tree is already empty\n");
            } else {
                BSTDestroy(&root);
                printf("the tree has been destroyed");
            }
        } else if (command == 7) {
            int depth = BSTDepth(root);
            printf("Depth of the tree is %d\n", depth);
        } else if (command == 8) {
            if (IsEmpty(&root)) {
                printf("The tree is already empty\n");
            } else {
                BSTDestroy(&root);
                break;
            }
            
            
        }
    }
}