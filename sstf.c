#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find the nearest request
int find_min_index(int req[], int visited[], int head_pos, int n) {
    int min = INT_MAX, index = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && abs(head_pos - req[i]) < min) {
            min = abs(head_pos - req[i]);
            index = i;
        }
    }
    return index;
}

void sstf(int req[], int visited[], int head_pos, int n) {
    int total_movement = 0;

    printf("\nSeek Sequence:\n");
    for (int i = 0; i < n; i++) {
        int index = find_min_index(req, visited, head_pos, n);
        visited[index] = 1;
        total_movement += abs(head_pos - req[index]);
        head_pos = req[index];
        printf("%d\t", head_pos);
    }
    printf("\nTotal head movement: %d\n", total_movement);
}

int main() {
    int n, head_pos, total_tracks;

    printf("Enter total number of tracks: ");
    scanf("%d", &total_tracks);

    printf("Enter number of requests: ");
    scanf("%d", &n);

    int req[n], visited[n];
    printf("Enter the requests:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
        visited[i] = 0;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head_pos);

    sstf(req, visited, head_pos, n);
    return 0;
}


/*
Enter total number of tracks: 200
Enter number of requests: 8
Enter the requests:
98 183 37 122 14 124 65 67
Enter initial head position: 53

Seek Sequence:
65    67    37    14    98    122    124    183
Total head movement: 208

*/

/*
📘 Short Algorithm

1.Input total disk size, requests, and initial head.
2.Mark all requests as unvisited.
3.From the current head, find the closest unvisited request.
4.Move the head to that request and mark it visited.
5.Repeat until all requests are served.
6.Print the sequence and total head movement.
*/