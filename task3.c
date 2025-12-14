#include <stdio.h>
#include <stdlib.h>

int main() {
    float *t = NULL;
    int n, add, i, ch;
    float th;
    FILE *fp;
    printf("Enter number of initial readings: ");
    scanf("%d", &n);

    t = (float *) malloc(n * sizeof(float));
    if (t == NULL) return 1;
    printf("Enter readings:\n");
    for (i = 0; i < n; i++) {
        printf("Reading %d: ", i + 1);
        scanf("%f", t + i);
    }
    while (1) {
        printf("\n1. Add readings\n");
        printf("2. Highest & Lowest\n");
        printf("3. Count above threshold\n");
        printf("4. Save summary\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &ch);
        if (ch == 1) {
            printf("How many to add: ");
            scanf("%d", &add);
            t = (float *) realloc(t, (n + add) * sizeof(float));
            if (t == NULL) return 1;
            for (i = n; i < n + add; i++) {
                printf("Reading %d: ", i + 1);
                scanf("%f", t + i);
            }
            n += add;
        }
        else if (ch == 2) {
            float hi = *(t + 0);
            float lo = *(t + 0);
            for (i = 1; i < n; i++) {
                float v = *(t + i);
                if (v > hi) hi = v;
                if (v < lo) lo = v;
            }
            printf("Highest = %.2f\n", hi);
            printf("Lowest  = %.2f\n", lo);
        }
        else if (ch == 3) {
            int count = 0;
            printf("Threshold: ");
            scanf("%f", &th);
            for (i = 0; i < n; i++) {
                if (*(t + i) > th) count++;
            }
            printf("Readings above threshold = %d\n", count);
        }
        else if (ch == 4) {
            fp = fopen("temperature_summary.txt", "w");
            if (fp == NULL) continue;
            float hi = *(t + 0);
            float lo = *(t + 0);
            for (i = 1; i < n; i++) {
                float v = *(t + i);
                if (v > hi) hi = v;
                if (v < lo) lo = v;
            }
            fprintf(fp, "Temperature Summary\n");
            fprintf(fp, "-------------------\n");
            for (i = 0; i < n; i++) {
                fprintf(fp, "Reading %d: %.2f\n", i + 1, *(t + i));
            }
            fprintf(fp, "\nHighest: %.2f\n", hi);
            fprintf(fp, "Lowest: %.2f\n", lo);
            fclose(fp);
            printf("Summary saved.\n");
        }
        else if (ch == 5) {
            break;
        }
    }
    free(t);
    return 0;
}
