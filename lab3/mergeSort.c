#include<stdio.h>
#include"item.h"
#include<string.h>
#include<math.h>

void merge(Item left[], int leftSize, Item right[], int rightSize, Item arr[]) {
    Item result[leftSize + rightSize];
    int leftIndex = 0;
    int rightIndex = 0;
    int resultIndex = 0;

    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (strcmp(left[leftIndex].key_str, right[rightIndex].key_str) < 0) {
            result[resultIndex] = left[leftIndex];
            leftIndex++;
        }
        else{
            result[resultIndex] = right[rightIndex];
            rightIndex++;
        }
        resultIndex++;
    }

    while (leftIndex < leftSize){
        result[resultIndex] = left[leftIndex];
        leftIndex++;
        resultIndex++;
    }

    while (rightIndex < rightSize){
        result[resultIndex] = right[rightIndex];
        rightIndex++;
        resultIndex++;
    }

    for (int i = 0; i < leftSize + rightSize; i++) {
        arr[i] = result[i];
    }
    
}


void mergeSort(Item arr[], int size) { 

    if (size <= 1) return;
    int mid = size / 2;

    Item left[mid];
    Item right[size-mid];

    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }

    for (int i = mid; i < size; i++) {
        right[i-mid] = arr[i];
    }
    
    mergeSort(left, mid);
    mergeSort(right, size - mid);

    merge(left, mid, right, size - mid, arr);       
}


int binarySearch(char* temp[], int len, char *key) {
    int low = 0;
    int high = len - 1;

    while (low <= high) {
        int mid = floor((low + high) / 2);
        char* guess = temp[mid];

        if (strcmp(guess, key) == 0) {
            return mid;
        } else if (strcmp(guess, key) > 0) {
            high = mid - 1;
        } else if (strcmp(guess, key) < 0) {
            low = mid + 1;
        }
    }
    
    return -1;
}

int main() {

    int len;
    printf("Enter number of elements: \n");
    scanf("%d", &len);

    Item arr[len];

    printf("Введите %d строк в таком формате: ключ(str value) прозаичный текст: \n", len);
    for (int i = 0; i < len; i++) {
        scanf("%s %d", arr[i].key_str, &arr[i].key_num);
        scanf(" %511[^\n]", arr[i].text);
    }       

    printf("-----------------------------------------\n");
    printf("элементы до сортировки: \n");
    for (int i = 0; i < len; i++) {
        printf("%s %d | %s\n", arr[i].key_str, arr[i].key_num, arr[i].text);
        printf("=========================\n");
    }

    printf("-----------------------------------------\n");
    printf("элементы после сортировки: \n");

    mergeSort(arr, len);

    for (int i = 0; i < len; i++) {
        printf("%s %d | %s\n", arr[i].key_str, arr[i].key_num, arr[i].text);
        printf("=========================\n");
    }
    
    char* temp[len];
    for (int i = 0; i < len; i++) {
        temp[i] = arr[i].key_str;
    }
   
    int amount_key;
    printf("Введите кол-во ключей для поиска: ");
    scanf("%d", &amount_key);

    for (int i = 0; i < amount_key; i++) {
        char search_key[50];
        printf("Введите ключ: ");
        scanf("%s", search_key);

        int target = binarySearch(temp, len, search_key);
        if (target >= 0) {
            printf("Ключ найден, вот вся соотаветствующая ему запись: \n");
            printf("%s %d | %s\n", arr[target].key_str, arr[target].key_num, arr[target].text);
        } else {
            printf("Такого ключа нет, код ошибки: %d\n", target);
        }
        
    }
    
}