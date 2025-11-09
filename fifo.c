//client_fifo.c (Client – writes to myfifo1, reads from myfifo2)

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUFF 1024

int main() {
    int fd1, fd2, c = 0;
    char *myfifo1 = "myfifo1";   // FIFO for writing data to server
    char *myfifo2 = "myfifo2";   // FIFO for reading data from server
    char buff[MAX_BUFF];         // Buffer to store user input
    char buff2[MAX_BUFF];        // Buffer to store data from server
    char ch;

    // Create FIFO myfifo1 (used for client → server communication)
    int res = mkfifo(myfifo1, 0777);
    if (res == -1) {
        printf("\nPipe 1 already exists or could not be created.\n");
    }

    // Get input string from user until '#' is entered
    printf("\nEnter the string (end with #):\n");
    while ((ch = getchar()) != '#') {
        buff[c++] = ch;
    }
    buff[c] = '\0';  // Null-terminate the string

    // Open FIFO myfifo1 in write-only mode and send data to server
    fd1 = open(myfifo1, O_WRONLY);
    write(fd1, buff, sizeof(buff));
    printf("\nContents written to pipe.\n");
    close(fd1);

    // Open FIFO myfifo2 in read-only mode and read processed data from server
    fd2 = open(myfifo2, O_RDONLY);
    read(fd2, buff2, MAX_BUFF);

    // Display the received processed result from server
    printf("\nContents received from server:\n%s\n", buff2);
    close(fd2);

    // Remove second pipe (optional cleanup)
    unlink(myfifo2);

    return 0;
}


//server_fifo.c (Server – reads from myfifo1, writes to myfifo2)
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUF 1024

int main() {
    int words = 0, lines = 0, chars = 0;
    FILE *fp;
    char buf[MAX_BUF];
    int fd, fd1, i = 0;

    char *myfifo1 = "myfifo1";  // FIFO for client → server
    char *myfifo2 = "myfifo2";  // FIFO for server → client

    // Create FIFO myfifo2 (used for sending data back to client)
    mkfifo(myfifo2, 0777);

    // Open FIFO myfifo1 in read-only mode and receive data from client
    fd = open(myfifo1, O_RDONLY);
    read(fd, buf, MAX_BUF);

    printf("\nMessage received from client: %s\n", buf);

    // Count number of words, lines, and characters
    while (buf[i] != '\0') {
        if (buf[i] == ' ' || buf[i] == '\n')
            words++;
        else
            chars++;

        if (buf[i] == '\n')
            lines++;

        i++;
    }
    words++;
    lines++;

    // Display results on server terminal
    printf("No. of lines: %d\n", lines);
    printf("No. of words: %d\n", words);
    printf("No. of characters: %d\n", chars);

    // Write results to a file
    fp = fopen("a.txt", "w+");
    fprintf(fp, "No. of lines: %d\n", lines);
    fprintf(fp, "No. of words: %d\n", words);
    fprintf(fp, "No. of characters: %d\n", chars);
    fclose(fp);

    // Close and remove myfifo1 after reading
    close(fd);
    unlink(myfifo1);

    // Send file contents back to client via myfifo2
    fd1 = open(myfifo2, O_WRONLY);
    system("cat a.txt > myfifo2");
    close(fd1);

    return 0;
}

/*
gcc server_fifo.c -o server_fifo
gcc client_fifo.c -o client_fifo
./server_fifo
./client_fifo

i/p:
Hello world how are you#

o/p:
CLIENT TERMINAL:
Enter the string (end with #):
Hello world how are you#
Contents written to pipe.

Contents received from server:
No. of lines: 1
No. of words: 5
No. of characters: 19

SERVER TERMINAL:
Message received from client: Hello world how are you
No. of lines: 1
No. of words: 5
No. of characters: 19

FILE a.txt CREATED BY SERVER:
No. of lines: 1
No. of words: 5
No. of characters: 19
*/

/*Algorithm: FIFO Client–Server Communication

Client Process (client_fifo.c):
1.Start
2.Create a named pipe myfifo1 using mkfifo().
3.Take input string from user until the # character is entered.
4.Open myfifo1 in write-only mode.
5.Write the entered string into myfifo1.
6.Close myfifo1.
7.Open myfifo2 in read-only mode.
8.Read the processed result (line, word, char count) sent by the server.
9.Display the received contents on the screen.
10.Close myfifo2 and delete it using unlink().
11.End

Server Process (server_fifo.c):
1.Start
2.Create a named pipe myfifo2 using mkfifo().
3.Open myfifo1 in read-only mode.
4.Read the string sent by the client through myfifo1.
5.Initialize counters: lines = 0, words = 0, chars = 0.
6.Traverse the received string and count:
-Increment words when space or newline occurs.
-Increment chars for every non-space character.
-Increment lines when newline occurs.
7.Display the counts on the server terminal.
8.Write the counts to a file a.txt.
9.Open myfifo2 in write-only mode.
10.Send the contents of a.txt back to the client using myfifo2.
11.Close and remove both FIFOs.
12.End
*/
