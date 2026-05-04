#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "lexemme.h"
#include "stackL.h"
#include "stackT.h"
#include "tree.h"

int GetPriority(char c) {
    switch (c) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default: return 0;
    }
}

NodeNT* simplify(NodeNT *root) {
    if (root == NULL) return NULL;

    NodeNT *child = root->child;
    while (child) {
        simplify(child);
        child = child->brother;
    }

    if (root->lex.Type == PRIMITIVE_OPERATOR &&
    root->lex.Value.symbol == '+') {

    int sum = 0;
    NodeNT *newChildren = NULL;
    NodeNT *tail = NULL;

    NodeNT *curr = root->child;

    while (curr) {
        NodeNT *next = curr->brother;

        if (curr->lex.Type == NUMBER) {
            sum += curr->lex.Value.number;
            free(curr);
        }

        else if (curr->lex.Type == PRIMITIVE_OPERATOR &&
                 curr->lex.Value.symbol == '+') {

            NodeNT *inner = curr->child;

            while (inner) {
                NodeNT *innerNext = inner->brother;

                if (inner->lex.Type == NUMBER) {
                    sum += inner->lex.Value.number;
                    free(inner);
                } else {
                    inner->brother = NULL;

                    if (tail == NULL) {
                        newChildren = inner;
                        tail = inner;
                    } else {
                        tail->brother = inner;
                        tail = inner;
                    }
                }

                inner = innerNext;
            }

            free(curr);
        }

        else {
            curr->brother = NULL;

            if (tail == NULL) {
                newChildren = curr;
                tail = curr;
            } else {
                tail->brother = curr;
                tail = curr;
            }
        }

        curr = next;
    }

    if (sum != 0) {
        NodeNT *num = CreateNodeNT(Number(sum));
        num->brother = newChildren;
        newChildren = num;
    }

    root->child = newChildren;
}

    return root;
}

StackL* Dijkstra() {
    char input[256];
    fgets(input, 256, stdin);

    StackL *output = CreateStackL();
    StackL *ops = CreateStackL();

    for (int i = 0; input[i]; i++) {
        char c = input[i];

        if (c == ' ' || c == '\n') continue;

        if (isdigit(c)) {
        int num = 0;

        while (isdigit(input[i])) {
            num = num * 10 + (input[i] - '0');
            i++;
        }

        i--;
        StackLPush(output, Number(num));
        } else if (isalpha(c)) {
            char str[2] = {c, '\0'};
            StackLPush(output, Variable(str));
        } else if (c == '(') {
            StackLPush(ops, Bracket(c));
        } else if (c == ')') {
            while (!StackLIsEmpty(ops) &&
                   StackLPeek(ops).Value.symbol != '(') {
                StackLPush(output, StackLPeek(ops));
                StackLPop(ops);
            }
            StackLPop(ops);
        } else {
            while (!StackLIsEmpty(ops) &&
                   GetPriority(StackLPeek(ops).Value.symbol) >= GetPriority(c)) {
                StackLPush(output, StackLPeek(ops));
                StackLPop(ops);
            }
            StackLPush(ops, PrimitiveOperator(c));
        }
    }

    while (!StackLIsEmpty(ops)) {
        StackLPush(output, StackLPeek(ops));
        StackLPop(ops);
    }

    DeleteStackL(&ops);
    return output;
}

int main() {
    printf("Введите математическое выражение: ");

    StackL *resultStack = Dijkstra(); 
    StackL *temp = CreateStackL();

    printf("\nВыражение в Обратной польской нотации (ОПЗ): ");

    StackL *displayStack = CreateStackL();

    while (!StackLIsEmpty(resultStack)) {
        StackLPush(displayStack, StackLPeek(resultStack));
        StackLPop(resultStack);
    }

    while (!StackLIsEmpty(displayStack)) {
        PrintLexemme(StackLPeek(displayStack), true);
        StackLPush(temp, StackLPeek(displayStack));
        StackLPop(displayStack);
    }

    StackL *final = CreateStackL();
    while (!StackLIsEmpty(temp)){
        StackLPush(final, StackLPeek(temp));
        StackLPop(temp);
    }

    printf("\n");

    printf("\nДерево выражения:\n");
    NodeNT *root = buildTree(final);
    PrintNTree(root, 0);

    root = simplify(root);

    printf("\nПосле упрощения:\n");
    PrintNTree(root, 0);
    DeleteStackL(&resultStack);
    DeleteStackL(&displayStack);
    DeleteStackL(&temp);
    DeleteStackL(&final);
    DestroyNTree(&root);

    return 0;
}