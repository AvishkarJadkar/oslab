#include <stdio.h>
#include <stdlib.h>

int main() {
    int size_of_disk, n, initial_head, direction;
    int req[100], total_movement = 0, temp;

    printf("Enter the size of disk: ");
    scanf("%d", &size_of_disk);

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    printf("Enter the direction (0: lower, 1: higher): ");
    scanf("%d", &direction);

    // Sort the requests
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (req[j] > req[j + 1]) {
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        if (initial_head < req[i]) {
            index = i;
            break;
        }
    }

    printf("\nSeek Sequence:\n");

    if (direction == 1) { // Move towards higher end first
        for (int i = index; i < n; i++) {
            total_movement += abs(req[i] - initial_head);
            initial_head = req[i];
            printf("%d\t", initial_head);
        }
        // Jump to end of disk
        total_movement += abs((size_of_disk - 1) - initial_head);
        initial_head = 0;
        // Jump from end to start
        total_movement += (size_of_disk - 1);
        for (int i = 0; i < index; i++) {
            total_movement += abs(req[i] - initial_head);
            initial_head = req[i];
            printf("%d\t", initial_head);
        }
    } else { // Move towards lower end first
        for (int i = index - 1; i >= 0; i--) {
            total_movement += abs(initial_head - req[i]);
            initial_head = req[i];
            printf("%d\t", initial_head);
        }
        total_movement += abs(initial_head - 0);
        initial_head = size_of_disk - 1;
        total_movement += (size_of_disk - 1);
        for (int i = n - 1; i >= index; i--) {
            total_movement += abs(req[i] - initial_head);
            initial_head = req[i];
            printf("%d\t", initial_head);
        }
    }

    printf("\nTotal head movement: %d\n", total_movement);
    return 0;
}


/*
Enter the size of disk: 200
Enter the number of requests: 8
Enter the requests:
98 183 37 122 14 124 65 67
Enter the initial head position: 53
Enter the direction (0: lower, 1: higher): 1

Seek Sequence:
65    67    98    122    124    183    199    0    14    37
Total head movement: 388

*/

/*
📘 Short Algorithm
1.Input total disk size, request sequence, initial head, and direction.
2.Sort the requests.
3.If moving higher:
-Service requests greater than the head.
-Jump to the end of the disk, then to 0, then serve remaining requests.
4.If moving lower:
-Service requests lower than the head.
-Jump to 0, then to end, then serve remaining requests.
5.Compute total head movement.
*/