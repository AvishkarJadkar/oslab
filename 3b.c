#include <stdio.h>

struct Process {
    int PID;
    int ArrivalTime;
    int BrustTime;
    int remTime;
    int CompletionTime;
    int WaitingTime;
    int TurnaroundTime;
};

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Input processes
    for (int i = 0; i < n; i++) {
        proc[i].PID = i + 1;
        printf("Enter Arrival Time for P%d: ", proc[i].PID);
        scanf("%d", &proc[i].ArrivalTime);
        printf("Enter Burst Time for P%d: ", proc[i].PID);
        scanf("%d", &proc[i].BrustTime);
        proc[i].remTime = proc[i].BrustTime;
        proc[i].CompletionTime = 0;
        proc[i].WaitingTime = 0;
        proc[i].TurnaroundTime = 0;
    }
    scanf("\n");
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int time = 0;
    int completed = 0;
    int i = 0;  // process index to simulate cyclic behavior

    while (completed < n) {
        // If process has arrived and still remaining time
        if (proc[i].ArrivalTime <= time && proc[i].remTime > 0) {
            int exec_time = (proc[i].remTime > quantum) ? quantum : proc[i].remTime;

            // Execute process for exec_time units
            proc[i].remTime -= exec_time;
            time += exec_time;

            // If process finished now
            if (proc[i].remTime == 0) {
                completed++;
                proc[i].CompletionTime = time;
                proc[i].TurnaroundTime = proc[i].CompletionTime - proc[i].ArrivalTime;
                proc[i].WaitingTime = proc[i].TurnaroundTime - proc[i].BrustTime;
                if (proc[i].WaitingTime < 0) proc[i].WaitingTime = 0;
            }
        } else {
            // If process not arrived or no remaining time, just increment time if nothing is running
            // Check if all processes are arrived, else advance time
            int all_arrived = 1;
            for (int j = 0; j < n; j++) {
                if (proc[j].remTime > 0 && proc[j].ArrivalTime > time) {
                    all_arrived = 0;
                    break;
                }
            }
            if (!all_arrived) {
                time++;
                continue;
            }
        }

        // Move to next process cyclically
        i = (i + 1) % n;
    }

    // Display results
    float totalWT = 0, totalTAT = 0;
    printf("\nPID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWT += proc[i].WaitingTime;
        totalTAT += proc[i].TurnaroundTime;
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               proc[i].PID,
               proc[i].ArrivalTime,
               proc[i].BrustTime,
               proc[i].CompletionTime,
               proc[i].WaitingTime,
               proc[i].TurnaroundTime);
    }

    printf("\nAverage Waiting Time = %.2f", totalWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}

/*
Algorithm: Round Robin Scheduling with Arrival Time

Step 1:
Start and input the number of processes n.

Step 2:
For each process Pi, input:

Arrival Time

Burst Time
Initialize:
remTime = Burst Time, CompletionTime = 0, WaitingTime = 0, TurnaroundTime = 0.

Step 3:
Input the Time Quantum (q).

Step 4:
Initialize time = 0, completed = 0, and process index i = 0.

Step 5:
Repeat until all processes are completed (completed < n):

If process Pi has arrived (ArrivalTime ≤ time) and **remaining time > 0`:

Execute process for min(quantum, remTime) time units.

Decrease its remTime by the executed time.

Increase time by executed time.

If remTime == 0:

Mark process as completed.

Calculate

CompletionTime = time

TurnaroundTime = CompletionTime - ArrivalTime

WaitingTime = TurnaroundTime - BurstTime

Else, if no process has arrived yet → increment time by 1.

Move to the next process cyclically (i = (i + 1) % n).

Step 6:
After all processes are done, calculate:

Average Waiting Time

Average Turnaround Time

Step 7:
Display all results in a table format.

Step 8:
End.
*/