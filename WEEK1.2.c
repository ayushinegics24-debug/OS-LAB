#include <stdio.h>

int main() {
    int n, i, j;
    int burst[20], process[20];
    int waiting[20], turnaround[20], temp;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time for each process:\n");

    for(i = 0; i < n; i++) {
        printf("P%d: ", i+1);
        scanf("%d", &burst[i]);
        process[i] = i + 1;
    }


    for(i = 0; i < n; i++) {
        for(j = i + 1; j < n; j++) {
            if(burst[i] > burst[j]) {
                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    waiting[0] = 0;

    for(i = 1; i < n; i++) {
        waiting[i] = waiting[i-1] + burst[i-1];
    }


    for(i = 0; i < n; i++) {
        turnaround[i] = waiting[i] + burst[i];
        total_wt += waiting[i];
        total_tat += turnaround[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", process[i], burst[i], waiting[i], turnaround[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt/n);
    printf("\nAverage Turnaround Time = %.2f", total_tat/n);

    return 0;
}
