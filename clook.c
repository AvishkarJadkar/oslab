#include <stdio.h>
#include <stdlib.h>

int main() {
    int RQ[100], n, TotalHeadMovement = 0, initial, move;
    int size_of_disk = 0;

    // Step 1: Input section
    printf("Enter the size of disk: ");
    scanf("%d", &size_of_disk);

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &RQ[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initial);

    printf("Enter the direction (0: lower, 1: higher): ");
    scanf("%d", &move);

    // Step 2: Sort the requests in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (RQ[j] > RQ[j + 1]) {
                int temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }

    // Step 3: Find the first request greater than initial head
    int index = 0;
    while (index < n && RQ[index] < initial) {
        index++;
    }

    printf("\nSeek Sequence:\n");

    // Step 4: Move towards higher values first
    if (move == 1) {
        for (int i = index; i < n; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
            printf("%d\t", initial);
        }

        // Jump back to the lowest request (C-LOOK wraps around)
        for (int i = 0; i < index; i++) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
            printf("%d\t", initial);
        }
    }
    // Step 5: Move towards lower values first
    else {
        for (int i = index - 1; i >= 0; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
            printf("%d\t", initial);
        }

        // Wrap to highest request
        for (int i = n - 1; i >= index; i--) {
            TotalHeadMovement += abs(RQ[i] - initial);
            initial = RQ[i];
            printf("%d\t", initial);
        }
    }

    // Step 6: Output total movement
    printf("\nTotal head movement: %d\n", TotalHeadMovement);
    return 0;
}

/*Enter the size of disk: 200
Enter the number of requests: 8
Enter the requests:
98 183 37 122 14 124 65 67
Enter the initial head position: 53
Enter the direction (0: lower, 1: higher): 1

Seek Sequence:
65    67    98    122    124    14    37
Total head movement: 208
*/

/*  ALGORITHM:
1.Input total disk size, request sequence, initial head position, and direction.
2.Sort the request queue in ascending order.
3.Find the index of the first request greater than the head position.
4.If moving towards higher:
-Serve higher requests, then jump to the lowest and continue.
5.If moving towards lower:
-Serve lower requests, then jump to the highest and continue.
6.Calculate and print total head movement.*/