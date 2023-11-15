#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int finish[MAX_PROCESSES];

int processes, resources;

void initialize() {
    printf("Enter number of processes: ");
    scanf("%d", &processes);

    printf("Enter number of resources: ");
    scanf("%d", &resources);

    printf("Enter available resources: \n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter maximum resources that can be allocated to each process: \n");
    for (int i = 0; i < processes; i++) {
        printf("For process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
        finish[i] = 0;
    }

    printf("Enter resources currently allocated to each process: \n");
    for (int i = 0; i < processes; i++) {
        printf("For process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
}

int safetyCheck() {
    int work[MAX_RESOURCES];
    int finishCount = 0;

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    while (finishCount < processes) {
        int found = 0;

        for (int i = 0; i < processes; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < resources; j++) {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == resources) {
                    for (int k = 0; k < resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                    finishCount++;
                }
            }
        }

        if (found == 0) {
            return 0; // Unsafe state
        }
    }
    return 1; // Safe state
}

int requestResources(int process, int request[]) {
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[process][i] || request[i] > available[i])
            return 0;
    }

    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (safetyCheck())
        return 1; // Request can be granted
    else {
        // Revert changes if it leads to an unsafe state
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return 0; // Request cannot be granted
    }
}

int releaseResources(int process, int release[]) {
    for (int i = 0; i < resources; i++) {
        if (release[i] > allocation[process][i])
            return 0;
    }

    for (int i = 0; i < resources; i++) {
        available[i] += release[i];
        allocation[process][i] -= release[i];
        need[process][i] += release[i];
    }

    return 1;
}

int main() {
    initialize();

    printf("Safety check result: %s\n", safetyCheck() ? "System is in a safe state" : "System is in an unsafe state");

    // Example request and release of resources
    int process = 0;
    int request[MAX_RESOURCES] = {1, 2, 3}; // Change the request values
    if (requestResources(process, request))
        printf("Request for resources by process %d granted.\n", process);
    else
        printf("Request for resources by process %d denied.\n", process);

    int release[MAX_RESOURCES] = {2, 1, 1}; // Change the release values
    if (releaseResources(process, release))
        printf("Resources released by process %d.\n", process);
    else
        printf("Error releasing resources by process %d.\n", process);

    return 0;
}
