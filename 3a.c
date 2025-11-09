#include <stdio.h>
#include <limits.h>

struct Assignment3 {
    int PID;
    int ArrivalTime;
    int BrustTime;
    int remTime;
    int CompletionTime;
    int WaitingTime;
    int TurnaroundTime;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Assignment3 proc[n];

    // Input processes
    for (int i = 0; i < n; i++) {
        proc[i].PID = i + 1;
        printf("Enter Arrival Time for P%d: ", proc[i].PID);
        scanf("%d", &proc[i].ArrivalTime);
        printf("Enter Burst Time for P%d: ", proc[i].PID);
        scanf("%d", &proc[i].BrustTime);
        proc[i].remTime = proc[i].BrustTime;  // Initialize remaining time
    }

    int complete = 0, time = 0, minm = INT_MAX;
    int shortest = -1, finish_time;
    int check = 0;

    while (complete != n) {
        // Find the process with the smallest remaining time at current time
        minm = INT_MAX;
        shortest = -1;
        for (int j = 0; j < n; j++) {
            if (proc[j].ArrivalTime <= time && proc[j].remTime < minm && proc[j].remTime > 0) {
                minm = proc[j].remTime;
                shortest = j;
                check = 1;
            }
        }

        
        if (check == 0) {
            time++;
            continue;
        }

        // Execute the shortest process
        proc[shortest].remTime--;

        // If process is finished
        if (proc[shortest].remTime == 0) {
            complete++;
            check = 0;
            finish_time = time + 1;
            proc[shortest].CompletionTime = finish_time;
            proc[shortest].TurnaroundTime = finish_time - proc[shortest].ArrivalTime;
            proc[shortest].WaitingTime = proc[shortest].TurnaroundTime - proc[shortest].BrustTime;

            if (proc[shortest].WaitingTime < 0)
                proc[shortest].WaitingTime = 0;
        }

        time++;
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
Algorithm: Shortest Job First (Preemptive) Scheduling

Step 1:
Start and input the number of processes n.

Step 2:
For each process Pi, input:

Arrival Time

Burst Time
Initialize:
RemainingTime = BurstTime.

Step 3:
Set time = 0, complete = 0.

Step 4:
Repeat until all processes are completed (complete != n):

Find the process with the minimum remaining time among all processes that have arrived (ArrivalTime ≤ time) and not yet completed (RemainingTime > 0).

If no process is found, increment time by 1 and continue.

Step 5:
Execute that process for 1 time unit (decrease RemainingTime by 1).

Step 6:
If a process finishes (RemainingTime == 0):

Increment complete.

Calculate:

CompletionTime = time + 1

TurnaroundTime = CompletionTime - ArrivalTime

WaitingTime = TurnaroundTime - BurstTime.

Step 7:
After all processes finish, calculate and display:

Average Waiting Time

Average Turnaround Time
and show the process table.

Step 8:
End.
*/