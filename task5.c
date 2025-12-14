#include <stdio.h>
#include <stdlib.h>

struct Rental {
    char customerName[50];
    float duration;
    float rate;
    float cost;
};
int main() {
    struct Rental *r = NULL;
    int n, add, i, ch;
    FILE *fp;

    printf("Enter number of initial rentals: ");
    scanf("%d", &n);
    r = (struct Rental *) malloc(n * sizeof(struct Rental));
    if (r == NULL) return 1;
    for (i = 0; i < n; i++) {
        printf("\nCustomer Name: ");
        scanf(" %[^\n]", (r + i)->customerName);

        printf("Rental Duration (hours/days): ");
        scanf("%f", &(r + i)->duration);

        printf("Rate per unit (e.g., per hour/day): ");
        scanf("%f", &(r + i)->rate);

        (r + i)->cost = (r + i)->duration * (r + i)->rate;
    }
    while (1) {
        printf("\n1. Add more rentals\n");
        printf("2. Display all rentals\n");
        printf("3. Save invoices to file\n");
        printf("4. Compute totals\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &ch);
        if (ch == 1) {
            printf("How many to add: ");
            scanf("%d", &add);
            r = (struct Rental *) realloc(r, (n + add) * sizeof(struct Rental));
            if (r == NULL) return 1;
            for (i = n; i < n + add; i++) {
                printf("\nCustomer Name: ");
                scanf(" %[^\n]", (r + i)->customerName);

                printf("Rental Duration (hours/days): ");
                scanf("%f", &(r + i)->duration);

                printf("Rate per unit (e.g., per hour/day): ");
                scanf("%f", &(r + i)->rate);

                (r + i)->cost = (r + i)->duration * (r + i)->rate;
            }
            n += add;
        }
        else if (ch == 2) {
            printf("\n--- Rental Records ---\n");
            for (i = 0; i < n; i++) {
                printf("Customer: %s | Duration: %.2f | Rate: %.2f | Cost: %.2f\n",
                       (r + i)->customerName,
                       (r + i)->duration,
                       (r + i)->rate,
                       (r + i)->cost);
            }
        }
        else if (ch == 3) {
            fp = fopen("Rental_Invoices.txt", "a");
            if (fp == NULL) continue;
            for (i = 0; i < n; i++) {
                fprintf(fp, "%s, %.2f, %.2f, %.2f\n",
                        (r + i)->customerName,
                        (r + i)->duration,
                        (r + i)->rate,
                        (r + i)->cost);
            }
            fclose(fp);
            printf("Invoices saved to Rental_Invoices.txt\n");
        }
        else if (ch == 4) {
            float total = 0;
            float high = *( &((r + 0)->duration) );
            for (i = 0; i < n; i++) {
                total += (r + i)->duration;
                if ((r + i)->duration > high) high = (r + i)->duration;
            }
            printf("Total Rental Time = %.2f\n", total);
            printf("Highest Single Rental Duration = %.2f\n", high);
        }
        else if (ch == 5) {
            break;
        }
    }
    free(r);
    return 0;
}
