#include <stdio.h>

// Function to implement Optimal Page Replacement Algorithm
void optimal(char string[], int frameSize, int count) {
    int faults = 0, end = 0;
    char frame[frameSize];

    printf("Page\tFrame\t\tPage Fault\n");
    printf("====================================\n");

    for (int i = 0; i < count; i++) {
        int found = 0;

        // Check if the current page already exists in the frame
        for (int j = 0; j < end; j++) {
            if (frame[j] == string[i]) {
                found = 1;
                break;
            }
        }

        // If page not found → page fault occurs
        if (!found) {
            faults++;

            // If there is still space in frame → directly insert
            if (end < frameSize) {
                frame[end++] = string[i];
            } 
            else {
                // Find the page to replace using Optimal logic
                int replace = -1, farthest = i;

                for (int j = 0; j < end; j++) {
                    int k;

                    // Find next use of current frame page
                    for (k = i + 1; k < count; k++) {
                        if (frame[j] == string[k])
                            break;
                    }

                    // If a page is not used again, replace it immediately
                    if (k == count) {
                        replace = j;
                        break;
                    }

                    // Keep track of the page used farthest in future
                    if (k > farthest) {
                        farthest = k;
                        replace = j;
                    }
                }

                // Replace the chosen page
                if (replace != -1)
                    frame[replace] = string[i];
            }

            // Print current frame state with page fault = Y
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\t\tY\n");
        } 
        else {
            // Page found in frame → No page fault
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\t\tN\n");
        }
    }

    // Final result
    printf("\nTotal Page Faults: %d\n", faults);
}

int main() {
    char string[50];
    int frameSize, count = 0;

    // Input reference string
    printf("Enter the reference string: ");
    scanf("%s", string);

    // Input number of frames
    printf("Enter the frame size: ");
    scanf("%d", &frameSize);

    // Count total pages in reference string
    while (string[count] != '\0')
        count++;

    // Call Optimal Page Replacement function
    optimal(string, frameSize, count);

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
A       A B C           Y
C       A B C           N
B       A B C           N
E       E B C           Y

Total Page Faults: 6
*/

/*🧠 Algorithm: Optimal Page Replacement

Step 1:
Start the program and take input:

Reference string (sequence of pages)

Number of frames available in memory

Step 2:
Initialize an empty frame array and set the page fault counter to zero.

Step 3:
For each page in the reference string:

If the page is already present in the frame → No page fault.

Else → Page fault occurs.

Step 4:
If there is still space in the frame → directly insert the page.

Step 5:
If the frame is full →

For each page currently in the frame, find how far in the future it will be used again.

Replace the page that will not be used for the longest time (or not used again at all).

Step 6:
Repeat Steps 3–5 for all pages, and at the end, display the total number of page faults.*/