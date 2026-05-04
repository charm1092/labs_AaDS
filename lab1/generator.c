#include <stdio.h>
#include <string.h>

#include "person.h"

void usage()
{
    printf("Usage: program filename\n");
}

int readperson(person *p)
{
    if (scanf("%19s %d %c", p->lastName, &p->numOfClass, &p->letterOfClass) != 3)
        return 0;

    if (strcmp(p->lastName, "0") == 0)
        return 0;

    return 1;
}

int main(int argc, char* argv[])
{
    if (argc != 3 || strcmp(argv[1], "-f") != 0) {
        usage();
        return 1;
    }

    person p;
    FILE *file = fopen(argv[2], "wb");
    if (!file) {
        perror("Can't open file");
        return 2;
    }

    printf("Введите список учеников:\n");
    printf("Формат ввода: <lastName> <numOfClass> <letterOf Class>\n");
    printf("Example: Иванов 11 А\n");
    printf("Введите 0 для завершения.\n\n");

    while (readperson(&p)) {
        fwrite(&p, sizeof(p), 1, file);
    }

    fclose(file);
    return 0;
}