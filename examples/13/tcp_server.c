/*
 * tcp_server.c
 *
 * Summary:
 * A basic TCP server that listens on port 8080, accepts a single client connection,
 * receives a message, and sends a reply. Demonstrates the server-side logic of
 * the client-server model using sockets.
 *
 * Compile: gcc tcp_server.c -o tcp_server
 * Run: ./tcp_server
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addr_len = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // 1. Create a socket (IPv4, TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Define address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Accept connections from any IP
    address.sin_port = htons(PORT);        // Convert to network byte order

    // 3. Bind the socket to the IP/port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 4. Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // 5. Accept a connection
    client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addr_len);
    if (client_fd < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 6. Read data from client
    read(client_fd, buffer, BUFFER_SIZE);
    printf("Received from client: %s\n", buffer);

    // 7. Send response to client
    const char *response = "Hello from the server!";
    send(client_fd, response, strlen(response), 0);

    // 8. Clean up
    close(client_fd);
    close(server_fd);

    return 0;
}
