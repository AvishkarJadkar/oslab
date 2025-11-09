#include <stdio.h>

// Function to implement LRU Page Replacement
void lru(char string[], int frameSize, int count) {
    int faults = 0, end = 0;
    char frame[frameSize];
    int recent[frameSize]; // Stores the last used index of each frame

    printf("Page\tFrame\t\tPage Fault\n");
    printf("====================================\n");

    for (int i = 0; i < count; i++) {
        int found = 0, min = 0;

        // Check if the page is already present in the frame
        for (int j = 0; j < end; j++) {
            if (frame[j] == string[i]) {
                found = 1;
                recent[j] = i; // Update recent usage
                break;
            }
        }

        // If page not found → Page Fault occurs
        if (!found) { 
            faults++;

            // If there is still space in frame
            if (end < frameSize) {
                frame[end] = string[i];
                recent[end++] = i;
            } 
            // If frame is full → Replace least recently used page
            else {
                for (int j = 1; j < end; j++) {
                    if (recent[j] < recent[min])
                        min = j;
                }
                frame[min] = string[i];
                recent[min] = i;
            }

            // Display frame contents after page fault
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tY\n");
        } 
        else {
            // If page found → No page fault
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\tN\n");
        }
    }

    // Print total page faults
    printf("\nTotal Page Faults: %d\n", faults);
}

int main() {
    char string[50];
    int frameSize, count = 0;

    // Input reference string and frame size
    printf("Enter the reference string: ");
    scanf("%s", string);

    printf("Enter the frame size: ");
    scanf("%d", &frameSize);

    // Count number of pages in reference string
    while (string[count] != '\0') 
        count++;

    // Call LRU function
    lru(string, frameSize, count);

    return 0;
}

/*Enter the reference string: ABCDACBE
Enter the frame size: 3
Page    Frame           Page Fault
====================================
A       A               Y
B       A B             Y
C       A B C           Y
D       D B C           Y
A       D A C           Y
C       D A C           N
B       B A C           Y
E       E A C           Y

Total Page Faults: 7

*/


/*Short Stepwise Algorithm (LRU Page Replacement)
1.Start
2.Input the reference string and number of frames.
3.Initialize:
-frame[] → stores current pages
-recent[] → stores last used index for each page
-faults = 0, end = 0
4.For each page in the reference string:
a. Check if the page exists in frame[].
b. If found: update recent[] (no page fault).
c. If not found:
-Increment faults.
-If there’s free space → insert page.
-Else → replace page with least recently used one (smallest value in recent[]).
5.Display each step with page fault status.
6.After all pages processed → print total page faults.
7.End*/