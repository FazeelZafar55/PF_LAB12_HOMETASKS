#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int totalRec(int *a,int n){
    if(n==0) return 0;
    return a[n-1] + totalRec(a,n-1);
}

int main(){
    int *gates=NULL;
    int n=0,choice;
    FILE *fp;
    time_t t;
    char ts[100];

    while(1){
        printf("\n1 Add Gate\n2 View Summary\n3 Save And Exit\nChoice: ");
        scanf("%d",&choice);
        if(choice==1){
            n++;
            gates=realloc(gates,n*sizeof(int));
            printf("Enter headcount for Gate %d: ",n);
            scanf("%d",&gates[n-1]);
        }
        else if(choice==2){
            if(n==0){
                printf("No gates added\n");
                continue;
            }
            int max=gates[0],pos=1;
            for(int i=1;i<n;i++){
                if(*(gates+i)>max){
                    max=*(gates+i);
                    pos=i+1;
                }
            }
            printf("\nTotal Attendees: %d\n",totalRec(gates,n));
            printf("Gate With Highest Attendance: Gate %d (%d)\n",pos,max);
        }
        else if(choice==3){
            fp=fopen("attendance.txt","a");
            time(&t);
            strftime(ts,sizeof(ts),"%Y-%m-%d %H:%M:%S",localtime(&t));

            fprintf(fp,"Timestamp: %s\n",ts);
            for(int i=0;i<n;i++){
                fprintf(fp,"Gate %d: %d\n",i+1,gates[i]);
            }
            fprintf(fp,"Total: %d\n\n",totalRec(gates,n));
            fclose(fp);
            printf("Saved to attendance.txt\n");
            free(gates);
            break;
        }
    }
    return 0;
}
