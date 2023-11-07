#include <stdio.h>

int main() {
    int n, i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int arrival_time[n], burst_time[n], priority[n], remaining_time[n], completion_time[n];
    int currentTime = 0, totalCompleted = 0, highestPriorityProcess = -1;

    for (i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &arrival_time[i], &burst_time[i], &priority[i]);
        remaining_time[i] = burst_time[i];
        completion_time[i] = -1;
    }

    printf("\nGantt Chart:\n");

    while (totalCompleted < n) {
        highestPriorityProcess = -1;
        int highestPriority = 9999;

        for (i = 0; i < n; i++) {
            if (arrival_time[i] <= currentTime && remaining_time[i] > 0 && priority[i] < highestPriority) {
                highestPriority = priority[i];
                highestPriorityProcess = i;
            }
        }

        if (highestPriorityProcess == -1) {
            printf("   %d   |  ", currentTime);
            currentTime++;
        } else {
            printf("   %d   |  P%d", currentTime, highestPriorityProcess + 1);

            int completionTime = currentTime + 1;
            while (completionTime < currentTime + 1) {
                printf("-");
                completionTime++;
            }
            currentTime += 1;
            remaining_time[highestPriorityProcess] -= 1;

            if (remaining_time[highestPriorityProcess] == 0) {
                totalCompleted++;
                completion_time[highestPriorityProcess] = currentTime;
            }
        }
    }

    printf("\n\nProcess\tArrival Time\tBurst Time\tPriority\tCompletion Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], priority[i], completion_time[i]);
    }

    return 0;
}