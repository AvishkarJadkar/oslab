#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Bubble Sort (Parent Process)
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort (Child Process)
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n, i;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t pid = fork(); // Create a new process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    else if (pid == 0) {
        // Child Process
        printf("\nChild Process (PID: %d)\n", getpid());
        printf("Sorting using Insertion Sort...\n");

        insertionSort(arr, n);

        printf("Child Process Sorted Array: ");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    else {
        // Parent Process
        wait(NULL); // Wait for child process to finish
        printf("\nParent Process (PID: %d)\n", getpid());
        printf("Sorting using Bubble Sort...\n");

        bubbleSort(arr, n);

        printf("Parent Process Sorted Array: ");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}



/*Algorithm: Sorting Using Fork (Parent and Child Process)

Step 1:
Start the program and input the number of integers n.

Step 2:
Accept n integers and store them in an array arr.

Step 3:
Create a new process using the fork() system call.

Step 4:
Check the process type:

If fork() returns negative → print error and exit.

If fork() returns 0 → it’s the child process.

Otherwise → it’s the parent process.

Step 5 (Child Process):

Display the process ID.

Sort the array using Insertion Sort.

Display the sorted array (Child Process Sorted Array).

Step 6 (Parent Process):

Wait for the child process to finish using wait().

Display the process ID.

Sort the same array using Bubble Sort.

Display the sorted array (Parent Process Sorted Array).

Step 7:
End the program.*/