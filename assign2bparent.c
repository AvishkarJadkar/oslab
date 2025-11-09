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
