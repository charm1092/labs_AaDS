#ifndef __ITEM__
#define __ITEM__

typedef struct {
    char key_str[50];   // часть ключа (строка)
    int key_num;        // часть ключа (число)
    char text[512];     // значение (проза)
} Item;

#endif