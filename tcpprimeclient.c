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
    struct sockaddr_in client_addr;

    // Get port input
    printf("Enter Port: ");
    scanf("%d", &port);

    // Create socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Error creating socket");
        exit(1);
    }
    printf("Socket Created.\n");

    // Set up client address
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(port);
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sock_fd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        perror("Error connecting");
        close(sock_fd);
        exit(1);
    }
    printf("Connected to server.\n\n");

    int flag = 1;
    while (flag) {
        char message[20];
        memset(message, 0, sizeof(message));

        // Get number input
        printf("Enter a number (or 'quit' to exit): ");
        scanf("%s", message);

        // Send number to server
        send(sock_fd, message, strlen(message), 0);

        if (strcmp(message, "quit") == 0) {
            break;
        }

        // Receive response
        memset(msg, 0, sizeof(msg));
        recv(sock_fd, msg, sizeof(msg), 0);
        printf("Server: %s\n", msg);
    }

    close(sock_fd);
    printf("\nConnection closed.\n");
    return 0;
}
