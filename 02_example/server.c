#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[1024] = {0};

    // 1. Create socket (Layer 4 - Transport)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Bind socket to IP/Port (Layer 3 - Network)
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP address
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 3. Listen for incoming connections (Layer 4 - Transport)
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    // 4. Accept a client connection (Layer 5 - Session)
    int addrlen = sizeof(address);
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    if (new_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // 5. Read request from client (Layer 7 - Application)
    read(new_socket, buffer, 1024);
    printf("Request received:\n%s\n", buffer);

    // 6. Send HTTP response (Layer 7 - Application)
    char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>";
    send(new_socket, response, strlen(response), 0);

    // 7. Close connection (Layer 5 - Session)
    close(new_socket);
    close(server_fd);

    return 0;
}
