#include <stdio.h>

struct Process {
    int processID;
    int arrivalTime;
    int burstTime;
    int completionTime;
};

void findWaitingTime(struct Process processes[], int n, int waitingTime[]) {
    int serviceTime[n];

    for (int i = 0; i < n; i++) {
        serviceTime[i] = 0;
        waitingTime[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        serviceTime[i] = serviceTime[i - 1] + processes[i - 1].burstTime;
        waitingTime[i] = serviceTime[i] - processes[i].arrivalTime;

        if (waitingTime[i] < 0) {
            waitingTime[i] = 0;
        }
    }
}

void findTurnAroundTime(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = processes[i].burstTime + waitingTime[i];
    }
}

void findAverageTime(struct Process processes[], int n) {
    int waitingTime[n], turnaroundTime[n];
    int totalWaitingTime = 0, totalTurnaroundTime = 0;

    findWaitingTime(processes, n, waitingTime);
    findTurnAroundTime(processes, n, waitingTime, turnaroundTime);

    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].processID, processes[i].burstTime, waitingTime[i], turnaroundTime[i]);
    }

    printf("\nAverage waiting time: %.2f\n", (float)totalWaitingTime / (float)n);
    printf("Average turnaround time: %.2f\n", (float)totalTurnaroundTime / (float)n);
}

void sortProcessesByArrivalTime(struct Process processes[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int main() {
    struct Process processes[] = {
        {1, 0, 6, 0},
        {2, 1, 8, 0},
        {3, 2, 7, 0},
        {4, 3, 3, 0}
    };
    int n = sizeof(processes) / sizeof(processes[0]);

    sortProcessesByArrivalTime(processes, n);
    findAverageTime(processes, n);

    return 0;
}
