#include <stdio.h>
#include <stdlib.h>

int main() {
    int *steps = NULL;
    int hours = 0, addHours, i, threshold;
    int choice;
    FILE *fp;
    printf("Enter number of hours of step data: ");
    scanf("%d", &hours);

    steps = (int *)malloc(hours * sizeof(int));
    if (steps == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("\nEnter step count for each hour:\n");
    for (i = 0; i < hours; i++) {
        printf("Hour %d: ", i + 1);
        scanf("%d", (steps + i));  
    }
    while (1) {
        printf("\n===== FITNESS TRACKER MENU =====\n");
        printf("1. Add more hours (realloc)\n");
        printf("2. Compute maximum steps\n");
        printf("3. Compute total steps\n");
        printf("4. Count hours above threshold\n");
        printf("5. Save data to file\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("How many more hours to add: ");
            scanf("%d", &addHours);

            steps = (int *)realloc(steps, (hours + addHours) * sizeof(int));
            if (steps == NULL) {
                printf("Reallocation failed.\n");
                return 1;
            }

            printf("Enter step count for new hours:\n");
            for (i = hours; i < hours + addHours; i++) {
                printf("Hour %d: ", i + 1);
                scanf("%d", (steps + i));
            }
            hours += addHours;
            printf("Hours successfully added!\n");
        }else if (choice == 2) {
            int max = *(steps + 0);
            for (i = 1; i < hours; i++) {
                if (*(steps + i) > max) {
                    max = *(steps + i);
                }
            }
            printf("Maximum steps in an hour = %d\n", max);
        }else if (choice == 3) {
            int total = 0;
            for (i = 0; i < hours; i++) {
                total += *(steps + i);
            }
            printf("Total steps = %d\n", total);
        }
        else if (choice == 4) {
            int count = 0;
            printf("Enter threshold: ");
            scanf("%d", &threshold);
            for (i = 0; i < hours; i++) {
                if (*(steps + i) > threshold) {
                    count++;
                }
            }
            printf("%d hours have steps above %d\n", count, threshold);
        }
        else if (choice == 5) {
            fp = fopen("fitness_tracker.txt", "w");
            if (fp == NULL) {
                printf("File could not be opened.\n");
                continue;
            }
            fprintf(fp, "Fitness Tracker Hourly Steps Data\n");
            fprintf(fp, "---------------------------------\n");
            for (i = 0; i < hours; i++) {
                fprintf(fp, "Hour %d: %d steps\n", i + 1, *(steps + i));
            }
            fclose(fp);
            printf("Data saved to fitness_tracker.txt\n");
        }
        else if (choice == 6) {
            break;
        }
        else {
            printf("Invalid choice. Try again.\n");
        }
    }
    free(steps);
    return 0;
}
