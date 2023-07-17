#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8888
#define RANGE_MIN 50000
#define RANGE_MAX 80000

int main() {
    int sockz, newsockz;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    // Create socket
    sockz = socket(AF_INET, SOCK_STREAM, 0);
    if (sockz < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Set server address
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Bind socket to address
    if (bind(sockz, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error on binding");
        exit(1);
    }

    // Listen for incoming connections
    listen(sockz, 5);
    clilen = sizeof(cli_addr);

    // Accept client connection
    newsockz = accept(sockz, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockz < 0) {
        perror("Error on accept");
        exit(1);
    }

    // Generate random number
    srand(time(NULL));
    int random_number = RANGE_MIN + rand() % (RANGE_MAX - RANGE_MIN + 1);

    // Convert random number to string
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "%d", random_number);

    // Send random number to client
    if (write(newsockz, buffer, strlen(buffer)) < 0) {
        perror("Error writing to socket");
        exit(1);
    }

    // Close sockets
    close(newsockz);
    close(sockz);

    return 0;
}

