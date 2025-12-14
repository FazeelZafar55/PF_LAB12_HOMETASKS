#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Log {
    char bookTitle[100];
    char memberID[30];
    int checkoutTime;
    int returnDueDays;
    int dueDate;
};
int main() {
    struct Log *logs = NULL;
    int n, add, i, ch;
    FILE *fp;

    printf("Enter number of initial checkout logs: ");
    scanf("%d", &n);
    logs = (struct Log *) malloc(n * sizeof(struct Log));
    if (logs == NULL) return 1;
    for (i = 0; i < n; i++) {
        printf("\nBook Title: ");
        scanf(" %[^\n]", (logs + i)->bookTitle);

        printf("Member ID: ");
        scanf("%s", (logs + i)->memberID);

        printf("Checkout Time (day number): ");
        scanf("%d", &(logs + i)->checkoutTime);

        printf("Days until return due: ");
        scanf("%d", &(logs + i)->returnDueDays);

        (logs + i)->dueDate = (logs + i)->checkoutTime + (logs + i)->returnDueDays;
    }

    while (1) {
        printf("\n1. Add more logs\n");
        printf("2. Display logs\n");
        printf("3. Append to CSV file\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            printf("How many logs to add: ");
            scanf("%d", &add);
            logs = (struct Log *) realloc(logs, (n + add) * sizeof(struct Log));
            if (logs == NULL) return 1;
            for (i = n; i < n + add; i++) {
                printf("\nBook Title: ");
                scanf(" %[^\n]", (logs + i)->bookTitle);

                printf("Member ID: ");
                scanf("%s", (logs + i)->memberID);

                printf("Checkout Time (day number): ");
                scanf("%d", &(logs + i)->checkoutTime);

                printf("Days until return due: ");
                scanf("%d", &(logs + i)->returnDueDays);

                (logs + i)->dueDate = (logs + i)->checkoutTime + (logs + i)->returnDueDays;
            }
            n += add;
        }
        else if (ch == 2) {
            printf("\n--- Checkout Logs ---\n");
            for (i = 0; i < n; i++) {
                printf("Book: %s | Member: %s | Out: %d | Due in: %d | Due Date: %d\n",
                       (logs + i)->bookTitle,
                       (logs + i)->memberID,
                       (logs + i)->checkoutTime,
                       (logs + i)->returnDueDays,
                       (logs + i)->dueDate);
            }
        }
        else if (ch == 3) {
            fp = fopen("library_log.csv", "a");
            if (fp == NULL) continue;
            for (i = 0; i < n; i++) {
                fprintf(fp, "%s,%s,%d,%d,%d\n",
                        (logs + i)->bookTitle,
                        (logs + i)->memberID,
                        (logs + i)->checkoutTime,
                        (logs + i)->returnDueDays,
                        (logs + i)->dueDate);
            }
            fclose(fp);
            printf("Data appended to library_log.csv\n");
        }
        else if (ch == 4) {
            break;
        }
    }
    free(logs);
    return 0;
}
