#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

int is_prime(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    int sock_fd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    char buffer[256];

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("Error creating socket");
        exit(1);
    }
    printf("Socket created\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding");
        close(sock_fd);
        exit(1);
    }
    printf("Binded\n");

    if (listen(sock_fd, 5) < 0) {
        perror("Error listening");
        close(sock_fd);
        exit(1);
    }
    printf("Listening...\n");

    client_len = sizeof(client_addr);
    newsockfd = accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
    if (newsockfd < 0) {
        perror("Error accepting connection");
        close(sock_fd);
        exit(1);
    }
    printf("Client connected\n\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        recv(newsockfd, buffer, sizeof(buffer), 0);

        if (strcmp(buffer, "quit") == 0) {
            break;
        }

        int num = atoi(buffer);
        char response[50];

        if (is_prime(num)) {
            strcpy(response, "Prime");
        } else {
            strcpy(response, "Not Prime");
        }

        send(newsockfd, response, strlen(response), 0);
    }

    close(newsockfd);
    close(sock_fd);
    printf("\nConnection closed.\n");
    return 0;
}
