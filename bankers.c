#include <stdio.h>

// Function to calculate the Need matrix: Need[i][j] = Max[i][j] - Allocation[i][j]
void calculateNeed(int need[][10], int max[][10], int alloc[][10], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Function to check if the system is in a safe state
int isSafe(int n, int m, int avail[], int alloc[][10], int need[][10]) {
    int f[n], ans[n], ind = 0;

    // Initialize all processes as not finished
    for (int i = 0; i < n; i++)
        f[i] = 0;

    // Work array to store available resources
    int work[m];
    for (int i = 0; i < m; i++)
        work[i] = avail[i];

    int count = 0;

    // Try to find a safe sequence
    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (f[i] == 0) {
                int flag = 1;

                // Check if process i can be safely executed
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 0;
                        break;
                    }
                }

                // If all resources are available for this process
                if (flag) {
                    for (int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    ans[ind++] = i;
                    f[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        // If no process can be executed in this round → unsafe state
        if (!found) {
            printf("The system is not in a safe state.\n");
            return 0;
        }
    }

    // If all processes finished safely → safe state
    printf("The system is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < n - 1; i++)
        printf("P%d -> ", ans[i]);
    printf("P%d\n", ans[n - 1]);

    return 1;
}

// Function to handle resource requests dynamically
void resourceRequest(int n, int m, int avail[], int max[][10], int alloc[][10], int need[][10]) {
    int request[m], p;

    printf("Enter the process number (0 to %d): ", n - 1);
    scanf("%d", &p);

    printf("Enter the requested resources:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &request[i]);

    // Check for errors
    for (int i = 0; i < m; i++) {
        if (request[i] > max[p][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return;
        }
        if (request[i] > avail[i]) {
            printf("Error: Resources not available.\n");
            return;
        }
    }

    // Tentatively allocate resources
    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[p][i] += request[i];
        need[p][i] -= request[i];
    }

    // Check if the system remains safe after allocation
    if (isSafe(n, m, avail, alloc, need)) {
        printf("Request granted. System remains in a safe state.\n");
    } else {
        printf("Request denied. Rolling back to original state.\n");
        // Rollback allocation
        for (int i = 0; i < m; i++) {
            avail[i] += request[i];
            alloc[p][i] -= request[i];
            need[p][i] += request[i];
        }
    }
}

int main() {
    int n, m;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int alloc[10][10], max[10][10], avail[10], need[10][10];

    // Input Allocation matrix
    printf("Enter the Allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Max matrix
    printf("Enter the Max matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available resources
    printf("Enter the Available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Adjust available resources by subtracting allocated ones
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            avail[j] -= alloc[i][j];
        }
    }

    // Calculate Need matrix
    calculateNeed(need, max, alloc, n, m);

    // Check for initial safe state
    if (isSafe(n, m, avail, alloc, need)) {
        // Allow resource request if system is initially safe
        resourceRequest(n, m, avail, max, alloc, need);
    }

    return 0;
}


/*Algorithm: Banker’s Algorithm

1.Input:
-Number of processes (n) and resources (m).
-Allocation matrix, Max matrix, and Available resources.

2.Calculate Need Matrix:
-Need[i][j] = Max[i][j] - Allocation[i][j]

3.Check for Safe State:
-Initialize Work = Available, Finish[i] = false for all i.
-Find a process i such that:
    ~Finish[i] == false
    ~Need[i] <= Work
-If found:
    ~Work = Work + Allocation[i]
    ~Finish[i] = true
    ~Repeat until all processes are finished or no such process exists.
-If all Finish[i] == true → System is Safe
-Else → System is Unsafe

4.Resource Request Algorithm:
-Get process number p and its Request[p].
-If Request[p] > Need[p] → Error: exceeds maximum claim.
-Else if Request[p] > Available → Wait: not enough resources.
-Else:
    ~Temporarily allocate:
        ~Available = Available - Request[p]
        ~Allocation[p] = Allocation[p] + Request[p]
        ~Need[p] = Need[p] - Request[p]
-Run Safety Algorithm again.
    ~If safe → Grant request
    ~Else → Rollback changes

5.Output:
-Safe Sequence if safe
-“System not in safe state” if unsafe*/