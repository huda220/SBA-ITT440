
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888

int main() {
    int sockz;
    struct sockaddr_in serv_addr;
    char buffer[256];

    // Create socket
    sockz = socket(AF_INET, SOCK_STREAM, 0);
    if (sockz < 0) {
        perror("Error opening socket");
        exit(1);
    }

    // Set server address
    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(1);
    }

    // Connect to server
    if (connect(sockz, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }

    // Retrieve random number from server
    ssize_t n;
    while ((n = read(sockz, buffer, sizeof(buffer))) > 0) {
        printf("Random number from server: %s\n", buffer);
    }
    if (n < 0) {
        perror("Error reading from socket");
        exit(1);
    }

    // Close socket
    close(sockz);

    return 0;
}

