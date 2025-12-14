#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Medicine {
    char medicineName[50];
    int quantityAvailable;
    float unitPrice;
};

int main(){
    int n=0,choice,index;
    struct Medicine *inv=NULL;
    FILE *fp;

    while(1){
        printf("\n1 Add Medicine\n2 Remove Medicine\n3 View Summary\n4 Save And Exit\nChoice: ");
        scanf("%d",&choice);

        if(choice==1){
            n++;
            inv=realloc(inv,n*sizeof(struct Medicine));
            printf("Medicine Name: ");
            scanf("%s",inv[n-1].medicineName);
            printf("Quantity: ");
            scanf("%d",&inv[n-1].quantityAvailable);
            printf("Unit Price: ");
            scanf("%f",&inv[n-1].unitPrice);
        }
        else if(choice==2){
            if(n==0){
                printf("No medicines to remove\n");
                continue;
            }
            printf("Enter index to remove (1-%d): ",n);
            scanf("%d",&index);
            if(index<1 || index>n){
                printf("Invalid index\n");
                continue;
            }
            for(int i=index-1;i<n-1;i++){
                inv[i]=inv[i+1];
            }
            n--;
            inv=realloc(inv,n*sizeof(struct Medicine));
            printf("Medicine removed\n");
        }
        else if(choice==3){
            if(n==0){
                printf("No inventory\n");
                continue;
            }
            float total=0;
            for(int i=0;i<n;i++){
                total+=inv[i].quantityAvailable*inv[i].unitPrice;
            }
            printf("\nInventory Summary:\n");
            for(int i=0;i<n;i++){
                printf("%d. %s  Qty: %d  Price: %.2f\n",
                    i+1,inv[i].medicineName,
                    inv[i].quantityAvailable,
                    inv[i].unitPrice);
                if(inv[i].quantityAvailable<10){
                    printf("  LOW STOCK ALERT!\n");
                }
            }
            printf("Total Inventory Value: %.2f\n",total);
        }
        else if(choice==4){
            fp=fopen("medicine_inventory.txt","w");
            for(int i=0;i<n;i++){
                fprintf(fp,"%s,%d,%.2f\n",
                    inv[i].medicineName,
                    inv[i].quantityAvailable,
                    inv[i].unitPrice);
            }
            fclose(fp);
            printf("Saved to medicine_inventory.txt\n");
            free(inv);
            break;
        }
    }
    return 0;
}
