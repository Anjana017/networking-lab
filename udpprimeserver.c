#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

// Function to check if a number is prime
int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main() 
{
    int sock_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[256];

    // Create UDP socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("Error creating socket");
        exit(1);
    }
    printf("Socket created\n");

    // Set up server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding");
        close(sock_fd);
        exit(1);
    }
    printf("Binded\n");

    client_len = sizeof(client_addr);

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        // Receive message from client
        recvfrom(sock_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_len) ;

        if (strcmp(buffer, "quit") == 0) {
            printf("Client requested to quit.\n");
            break;
        }

        printf("Client sent: %s\n", buffer);
        int num = atoi(buffer);  // Convert string to integer

        char response[50];
        if (is_prime(num)) {
            strcpy(response, "Prime");
        } else {
            strcpy(response, "Not Prime");
        }

        // Send result to client
        sendto(sock_fd, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_len) ;
    }

    close(sock_fd);
    printf("Server closed.\n");
    return 0;
}
