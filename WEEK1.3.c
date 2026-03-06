#include <stdio.h>
#include <limits.h>

int main() {
    int n, i, time = 0, smallest;
    int arrival[20], burst[20], remaining[20];
    int waiting[20], turnaround[20];
    int completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i+1);
        scanf("%d %d", &arrival[i], &burst[i]);
        remaining[i] = burst[i];
    }

    while(completed < n) {
        smallest = -1;
        int min = INT_MAX;

        for(i = 0; i < n; i++) {
            if(arrival[i] <= time && remaining[i] > 0 && remaining[i] < min) {
                min = remaining[i];
                smallest = i;
            }
        }

        if(smallest == -1) {
            time++;
            continue;
        }

        remaining[smallest]--;
        time++;

        if(remaining[smallest] == 0) {
            completed++;
            int finish_time = time;

            turnaround[smallest] = finish_time - arrival[smallest];
            waiting[smallest] = turnaround[smallest] - burst[smallest];

            total_wt += waiting[smallest];
            total_tat += turnaround[smallest];
        }
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", i+1, arrival[i], burst[i], waiting[i], turnaround[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n", total_tat/n);

    return 0;
}
