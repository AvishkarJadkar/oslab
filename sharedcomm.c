//shm_writer.c (Server / Producer):
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

#define SZ 4096  // Shared memory size

int main() {
    int shm_id;      // Shared memory ID
    int *shm_ptr;    // Pointer to shared memory
    int data;        // Data to write

    // Create a shared memory segment with read/write permissions
    shm_id = shmget(IPC_PRIVATE, SZ, IPC_CREAT | 0666);
    if (shm_id < 0) {
        perror("Error creating shared memory");
        exit(1);
    }

    printf("Shared memory created with ID: %d\n", shm_id);

    // Attach the created shared memory to the process's address space
    shm_ptr = (int *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (int *)-1) {
        perror("Error attaching shared memory");
        exit(1);
    }

    printf("Shared memory attached at address %p\n", shm_ptr);

    // Get input data from user
    printf("Enter data to write to shared memory: ");
    scanf("%d", &data);

    // Write the data to shared memory
    *shm_ptr = data;
    printf("Data written to shared memory: %d\n", *shm_ptr);

    // Wait for client to read the data
    printf("Waiting for client to read data...\n");
    sleep(10);  // Gives time for the client process to read data

    // Detach the shared memory segment
    if (shmdt(shm_ptr) == -1) {
        perror("Error detaching shared memory");
        exit(1);
    }
    printf("Shared memory detached.\n");

    // Delete the shared memory segment
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("Error deleting shared memory");
        exit(1);
    }
    printf("Shared memory deleted.\n");

    return 0;
}

//shm_reader.c (Client / Consumer):
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>

#define SZ 4096  // Shared memory size

int main() {
    int shm_id;     // Shared memory ID (to be entered by user)
    int *shm_ptr;   // Pointer to shared memory

    // Ask the user for the shared memory ID (displayed by writer)
    printf("Enter shared memory ID: ");
    scanf("%d", &shm_id);

    // Attach to the existing shared memory segment
    shm_ptr = (int *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (int *)-1) {
        perror("Error attaching to shared memory");
        exit(1);
    }

    printf("Shared memory attached at address %p\n", shm_ptr);

    // Read data from shared memory
    printf("Data read from shared memory: %d\n", *shm_ptr);

    // Detach the shared memory
    if (shmdt(shm_ptr) == -1) {
        perror("Error detaching shared memory");
        exit(1);
    }
    printf("Shared memory detached.\n");

    return 0;
}


/*
1.Open 2 terminals
2.gcc shm_writer.c -o shm_writer
  gcc shm_reader.c -o shm_reader
3.run the writer first - ./shm_writer
4.o/p:
Shared memory created with ID: 12345
Shared memory attached at address 0x7f8c7f000000
Enter data to write to shared memory: 42
Data written to shared memory: 42
Waiting for client to read data...
5. run the reader in another terminal
./shm_reader
6.o/p:
Enter shared memory ID: 12345
Shared memory attached at address 0x7f8c7f100000
Data read from shared memory: 42
Shared memory detached.
7.after 10 sec in writer's terminal:
Shared memory detached.
Shared memory deleted.


O/P (WRITER TERMINAL):
Shared memory created with ID: 12345
Shared memory attached at address 0x7f90c0000000
Enter data to write to shared memory: 42
Data written to shared memory: 42
Waiting for client to read data...
Shared memory detached.
Shared memory deleted.

O/P (READER TERMINAL):
Enter shared memory ID: 12345
Shared memory attached at address 0x7f90c0100000
Data read from shared memory: 42
Shared memory detached.

*/

/*Quick Algorithm
Writer Process:
Start.
Create a shared memory segment using shmget().
Attach it using shmat().
Accept integer input from user.
Write data into shared memory.
Wait for client to read data (sleep(10)).
Detach using shmdt().
Delete shared memory using shmctl().
End.

Reader Process:
Start.
Take shared memory ID from user.
Attach to shared memory using shmat().
Read and display data stored by writer.
Detach from memory using shmdt().
End.*/