//child program
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    printf("\nChild Process (PID=%d): Array in reverse order:\n", getpid());

    if (argc < 2) {
        printf("No elements received.\n");
        return 1;
    }

    for (int i = argc - 1; i > 0; i--) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    return 0;
}


//parent program
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    // Sort the array in parent before fork
    bubble_sort(arr, n);
    printf("\nParent Process (PID=%d): Sorted array: ", getpid());
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: execute child_program with array as arguments
        char **args = malloc((n + 2) * sizeof(char *));
        args[0] = "./child_program"; // program name must match the compiled file

        for (int i = 0; i < n; i++) {
            args[i + 1] = malloc(12);
            snprintf(args[i + 1], 12, "%d", arr[i]);
        }
        args[n + 1] = NULL; // execve needs a NULL terminator

        execve("./child_program", args, NULL);
        perror("execve failed");
        exit(1);
    } else {
        wait(NULL); // Parent waits for child
        printf("\nParent Process: Child execution finished.\n");
    }

    return 0;
}


/*
Algorithm: Inter-Process Communication using fork() and execve()

Step 1:
Start and input the number of elements n and the array elements.

Step 2:
Sort the array in the parent process using Bubble Sort.

Step 3:
Display the sorted array in the parent process.

Step 4:
Create a new process using the fork() system call.

If fork() fails → print error and exit.

If pid == 0 → child process.

Else → parent process.

Step 5 (Child Process):

Prepare command-line arguments (convert sorted integers to strings).

Use execve() to replace the child process with the child program (child_program).

The child program receives the sorted array as command-line arguments.

Step 6 (Child Program):

Display the received array in reverse order.

Step 7 (Parent Process):

Wait for the child process to complete using wait().

Print a message after child execution finishes.

Step 8:
End.

*/
