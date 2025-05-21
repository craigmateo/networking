#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    /* 1. Create socket (Layer 4 - Transport)
     Socket indicates where and how to send traffic back and forth across a network
     The socket() function takes three arguments:
         - AF_INET: Specifies IPv4 addressing.
         - SOCK_STREAM: Specifies TCP (reliable connection-oriented communication).
         - 0: Default protocol (TCP in this case). */

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    /* 2. Bind socket to IP/Port (Layer 3 - Network)

    bind() attaches the socket to:
        - AF_INET (IPv4 family)
        - INADDR_ANY (allows connections from any IP)
        - htons(PORT) (converts port number to network byte order)

    */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Accept any incoming connections
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    /* 3. Listen for incoming connections (Layer 4 - Transport)
    listen() tells the OS to start waiting for incoming connections.
        - 3 is the backlog, meaning the OS queues up to 3 pending connections.
        - OSI Layer: Transport Layer (Layer 4)
        - Ensures that connections can be established reliably.
    */
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    /* 4. Accept a client connection (Layer 5 - Session)
        - accept() waits for a client to connect and creates a new socket for communication.
        - The new socket (new_socket) handles data transfer, while server_fd remains open for other connections.
    */
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    /* 5. Read data (Layer 7 - Application)
        - read() reads incoming data from the client.
        - Data is stored in the buffer.
    */
    read(new_socket, buffer, 1024);
    printf("Message received: %s\n", buffer);

    /* 6. Send response (Layer 7 - Application)
        - send() transmits a response to the client.
    */
    char *response = "Hello from server";
    send(new_socket, response, strlen(response), 0);

    // 7. Close connection (Layer 5 - Session)
    close(new_socket);
    close(server_fd);

    return 0;
}
