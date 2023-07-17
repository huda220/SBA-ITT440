#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define BUFFER_SIZE 256

int main() {
    pid_t child1, child2, child3;
    int pipe1[2], pipe2[2], pipe3[2];
    char buffer[BUFFER_SIZE];

    if (pipe(pipe1) < 0 || pipe(pipe2) < 0 || pipe(pipe3) < 0) {
        perror("Pipe creation failed");
        exit(1);
    }

    child1 = fork();  // Create first child

    if (child1 == 0) {
        // Child 1 process
        close(pipe1[1]);  // Close write end of pipe 1
        close(pipe2[0]);  // Close read end of pipe 2
        close(pipe3[0]);  // Close read end of pipe 3

        read(pipe1[0], buffer, BUFFER_SIZE);  // Read message from pipe 1
        printf("Child 1: The first child received message - %s\n", buffer);

        strcat(buffer, " Child 1");  // Modify the message
        write(pipe2[1], buffer, strlen(buffer) + 1);  // Write message to pipe 2

        close(pipe1[0]);
        close(pipe2[1]);
        close(pipe3[1]);

        exit(0);
    }

    child2 = fork();  // Create second child

    if (child2 == 0) {
        // Child 2 process
        close(pipe1[0]);  // Close read end of pipe 1
        close(pipe1[1]);  // Close write end of pipe 1
        close(pipe2[1]);  // Close write end of pipe 2
        close(pipe3[0]);  // Close read end of pipe 3

        read(pipe2[0], buffer, BUFFER_SIZE);  // Read message from pipe 2
        printf("Child 2: Second child received message - %s\n", buffer);

        strcat(buffer, " Child 2");  // Modify the message
        write(pipe3[1], buffer, strlen(buffer) + 1);  // Write message to pipe 3

        close(pipe2[0]);
        close(pipe3[1]);

        exit(0);
    }

    child3 = fork();  // Create third child

    if (child3 == 0) {
        // Child 3 process
        close(pipe1[0]);  // Close read end of pipe 1
        close(pipe1[1]);  // Close write end of pipe 1
        close(pipe2[0]);  // Close read end of pipe 2
        close(pipe2[1]);  // Close write end of pipe 2
        close(pipe3[1]);  // Close write end of pipe 3

        printf("Child 3: Signal message\n");

        close(pipe3[0]);

        exit(0);
    }

    // Parent process
    close(pipe1[0]);  // Close read end of pipe 1
    close(pipe2[0]);  // Close read end of pipe 2
    close(pipe3[0]);  // Close read end of pipe 3
    close(pipe3[1]);  // Close write end of pipe 3

    strcpy(buffer, "Parent: I am the parent.");
    write(pipe1[1], buffer, strlen(buffer) + 1);  // Write message to pipe 1

    close(pipe1[1]);

    wait(NULL);  // Wait for child processes to complete

    return 0;
}

