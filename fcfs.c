#include <stdio.h>

// Function to implement FIFO Page Replacement Algorithm
void fifo(char string[], int frameSize, int count) {
    int faults = 0;            // Counter for total page faults
    int front = 0, end = 0;    // 'front' -> oldest page, 'end' -> next empty position
    char frame[frameSize];     // Array to represent memory frames

    printf("Page\tFrame\t\tPage Fault\n");
    printf("====================================\n");

    // Loop through each page in the reference string
    for (int i = 0; i < count; i++) {
        int found = 0; // Flag to check if the page already exists in frame

        // Check if the current page already exists in frame
        for (int j = 0; j < end; j++) {
            if (frame[j] == string[i]) {
                found = 1;
                break;
            }
        }

        // If the page is not found -> Page Fault occurs
        if (!found) { 
            faults++;  // Increment page fault count

            // If there is still space in frame
            if (end < frameSize) {
                frame[end++] = string[i];  // Add page to next empty slot
            } else {
                // Replace the oldest page (FIFO logic)
                frame[front] = string[i];
                front = (front + 1) % frameSize;  // Move front pointer circularly
            }

            // Display current status
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\t\tY\n"); // Y = Page Fault occurred
        } 
        else {
            // Page already present (No Page Fault)
            printf("%c\t", string[i]);
            for (int k = 0; k < end; k++) {
                printf("%c ", frame[k]);
            }
            printf("\t\tN\n"); // N = No Page Fault
        }
    }

    // Display total page faults
    printf("====================================\n");
    printf("Total Page Faults: %d\n", faults);
}

// Main function
int main() {
    char string[50];
    int frameSize, count = 0;

    // Input reference string
    printf("Enter the reference string: ");
    scanf("%s", string);

    // Input frame size
    printf("Enter the frame size: ");
    scanf("%d", &frameSize);

    // Count the number of pages in the reference string
    while (string[count] != '\0') 
        count++;

    // Call FIFO function
    fifo(string, frameSize, count);

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
B       D A B           Y
E       E A B           Y
====================================
Total Page Faults: 7*/


/*Algorithm: FIFO Page Replacement

1.Start
2.Input the reference string and the number of frames.
3.Initialize:
-front = 0, end = 0, faults = 0
-Create an empty frame[] array of given frame size.
4.For each page in the reference string:
a. Check if the page already exists in the frame.
b. If page found:
    -No page fault (print “N”).
c. If page not found (fault):
-Increment faults.
-If frame not full: insert page at end.
-Else: replace the oldest page at position front.
-Move front pointer circularly → (front + 1) % frameSize.
-Print “Y” (page fault occurred).
5.After all pages processed, display total page faults.
6.End*/