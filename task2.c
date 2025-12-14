#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Student {
    char studentName[50];
    char rollNumber[20];
    int seatNumber;
};
int isAlnumRecursive(char *str, int index) {
    if (str[index] == '\0') {
        return 1; 
    }
    if (!isalnum(str[index])) {
        return 0; 
    }
    return isAlnumRecursive(str, index + 1); 
}

int main() {
    struct Student *arr = NULL;
    int count = 0, add, i, choice;
    FILE *fp;

    printf("Enter number of students to assign seats for: ");
    scanf("%d", &count);

    arr = (struct Student *)malloc(count * sizeof(struct Student));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (i = 0; i < count; i++) {
        printf("\n--- Student %d ---\n", i + 1);
        printf("Enter student name: ");
        scanf(" %[^\n]", (arr + i)->studentName);
        while (1) {
            printf("Enter roll number (alphanumeric only): ");
            scanf("%s", (arr + i)->rollNumber);
            if (isAlnumRecursive((arr + i)->rollNumber, 0)) {
                break;
            } else {
                printf("Invalid! Roll number must be alphanumeric.\n");
            }
        }
        printf("Enter seat number: ");
        scanf("%d", &(arr + i)->seatNumber);
    }
    while (1) {
        printf("\n======= EXAM SEATING MENU =======\n");
        printf("1. Add more students\n");
        printf("2. Display all seat assignments\n");
        printf("3. Save seating plan to seating.txt\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("How many students to add: ");
            scanf("%d", &add);
            arr = (struct Student *)realloc(arr, (count + add) * sizeof(struct Student));
            if (arr == NULL) {
                printf("Reallocation failed.\n");
                return 1;
            }
            for (i = count; i < count + add; i++) {
                printf("\n--- Student %d ---\n", i + 1);

                printf("Enter student name: ");
                scanf(" %[^\n]", (arr + i)->studentName);
                while (1) {
                    printf("Enter roll number (alphanumeric only): ");
                    scanf("%s", (arr + i)->rollNumber);
                    if (isAlnumRecursive((arr + i)->rollNumber, 0)) {
                        break;
                    } else {
                        printf("Invalid! Roll number must be alphanumeric.\n");
                    }
                }
                printf("Enter seat number: ");
                scanf("%d", &(arr + i)->seatNumber);
            }
            count += add;
            printf("Students added successfully.\n");
        }

        else if (choice == 2) {
            printf("\n===== SEATING ASSIGNMENTS =====\n");
            for (i = 0; i < count; i++) {
                printf("Student: %s | Roll: %s | Seat: %d\n",
                       (arr + i)->studentName,
                       (arr + i)->rollNumber,
                       (arr + i)->seatNumber);
            }
        }
        else if (choice == 3) {
            fp = fopen("seating.txt", "w");
            if (fp == NULL) {
                printf("Could not open file.\n");
                continue;
            }
            fprintf(fp, "UNIVERSITY EXAM SEATING PLAN\n");
            fprintf(fp, "------------------------------\n");
            for (i = 0; i < count; i++) {
                fprintf(fp, "Student: %s | Roll: %s | Seat: %d\n",
                        (arr + i)->studentName,
                        (arr + i)->rollNumber,
                        (arr + i)->seatNumber);
            }
            fclose(fp);
            printf("Seating plan saved to seating.txt\n");
        }
        else if (choice == 4) {
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }
    free(arr);
    return 0;
}
