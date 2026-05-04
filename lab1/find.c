#include <stdio.h>
#include <string.h>

#include "person.h"


static void usage(const char *prog)
{
    printf("Usage: %s -f <binary_file>\n", prog);
}

int main(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "-f") != 0) {
        usage(argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[2], "rb");
    if (!file) {
        perror("Can't open file");
        return 2;
    }

    person people[1000];
    int count = 0;

    while (count < (int)(sizeof(people) / sizeof(people[0])) &&
           fread(&people[count], sizeof(person), 1, file) == 1) {
        count++;
    }

    fclose(file);

    if (count == 0) {
        printf("File is empty (0 records).\n");
        return 0;
    }

    /* Print as a table */
    printf("%-4s %-20s %-10s %-10s\n", "#", "Фамилия", "Класс", "Буква класса");
    printf("------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-4d %-20s %-10d %-10c\n",
               i + 1,
               people[i].lastName,
               (int)people[i].numOfClass,
               people[i].letterOfClass);
    }

    printf("\nОднофамильцы в параллельных классах:\n");

    int found = 0;
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(people[i].lastName, people[j].lastName) == 0 &&
                people[i].numOfClass == people[j].numOfClass &&
                people[i].letterOfClass != people[j].letterOfClass) {

                found = 1;
                printf("%s: %d%c and %d%c\n",
                       people[i].lastName,
                       (int)people[i].numOfClass, people[i].letterOfClass,
                       (int)people[j].numOfClass, people[j].letterOfClass);
            }
        }
    }

    if (!found) {
        printf("No such surnames found.\n");
    }

    return 0;
}