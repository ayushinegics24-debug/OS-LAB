#include <stdio.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time of P%d: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Enter burst time of P%d: ", i + 1);
        scanf("%d", &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;


    for (int i = 0; i < n; i++) {
        if (p[i].arrival == 0) {
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while (completed < n) {
        if (front == rear) {
            int nextArrival = 1e9;
            for (int i = 0; i < n; i++) {
                if (p[i].remaining > 0 && p[i].arrival < nextArrival)
                    nextArrival = p[i].arrival;
            }
            time = nextArrival;
            for (int i = 0; i < n; i++) {
                if (!visited[i] && p[i].arrival <= time) {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];
        if (p[idx].remaining > tq) {
            time += tq;
            p[idx].remaining -= tq;
        } else {
            time += p[idx].remaining;
            p[idx].remaining = 0;
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            completed++;
        }

        for (int i = 0; i < n; i++) {
            if (!visited[i] && p[i].arrival <= time) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }


        if (p[idx].remaining > 0) {
            queue[rear++] = idx;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
    }

    float avgTAT = 0, avgWT = 0;
    for (int i = 0; i < n; i++) {
        avgTAT += p[i].turnaround;
        avgWT += p[i].waiting;
    }
    avgTAT /= n;
    avgWT /= n;

    printf("\nAverage Turnaround Time = %.2f", avgTAT);
    printf("\nAverage Waiting Time = %.2f\n", avgWT);

    return 0;
}
