#include<stdio.h>

int main() {
    int i, j, time, sum_wait=0, sum_tat=0, smallest;
    int at[10], bt[10], priority[10], wt[10], tat[10], rt[10], remain;
    int n;

    printf("Enter number of Process: ");
    scanf("%d",&n);
    remain=n;

    for(i=0; i<n; i++) {
        printf("Enter arrival time, burst time and priority for process p%d: ",i+1);
        scanf("%d%d%d",&at[i],&bt[i],&priority[i]);
        rt[i]=bt[i];
    }

    priority[9]=11;
    for(time=0; remain!=0; ) {
        smallest=9;
        for(i=0; i<n; i++) {
            if(at[i]<=time && priority[i]<priority[smallest] && rt[i]>0) {
                smallest=i;
            }
        }

        time+=rt[smallest];
        rt[smallest]=0;
        remain--;
        printf("P[%d]\t|\t%d\t|\t%d\n",smallest+1,time-at[smallest],time-at[smallest]-bt[smallest]);
        wt[smallest]=time-at[smallest]-bt[smallest];
        tat[smallest]=time-at[smallest];
        sum_wait+=time-at[smallest]-bt[smallest];
        sum_tat+=time-at[smallest];
    }

    printf("\n\nAverage waiting time = %f\n",sum_wait*1.0/n);
    printf("Average Turnaround time = %f",sum_tat*1.0/5);

    return 0;
}
