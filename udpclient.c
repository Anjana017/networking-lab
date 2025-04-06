#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() 
{
    int port;
    int sock_fd;
    char msg[200];
    struct sockaddr_in client;
    // Get port input
    printf("Enter Port: ");
    scanf("%d", &port);
    // Create UDP socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("Error creating socket");
        exit(1);
    }
    printf("Socket Created.\n");
    // Set up client (server destination) address
    client.sin_family = AF_INET;
    client.sin_port = htons(port);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");  // Change IP if needed
    while (1) {
        char message[200];
        memset(message, 0, sizeof(message));
        printf("Client: ");
        scanf("%s", message);
        // Send message
        sendto(sock_fd, message, strlen(message), 0, (struct sockaddr *)&client, sizeof(client));
        // If "quit", break the loop
        if (strcmp(message, "quit") == 0) {
            break;
        }
        // Receive server response
        memset(msg, 0, sizeof(msg));
        recvfrom(sock_fd, msg, sizeof(msg), 0, NULL, NULL);
        printf("Server: %s\n", msg);
    }
    // Close socket
    close(sock_fd);
    printf("Connection closed.\n");
    return 0;
}
