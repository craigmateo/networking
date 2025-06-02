/*
 * tcp_client.c
 *
 * Summary:
 * A basic TCP client that connects to a server on localhost:8080,
 * sends a message, and waits for a reply. Demonstrates client-side
 * socket communication in the client-server model.
 *
 * Compile: gcc tcp_client.c -o tcp_client
 * Run: ./tcp_client
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // 1. Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 2. Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address or Address not supported\n");
        return -1;
    }

    // 3. Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return -1;
    }

    // 4. Send message to server
    const char *hello = "Hello from the client!";
    send(sock, hello, strlen(hello), 0);

    // 5. Receive response
    read(sock, buffer, BUFFER_SIZE);
    printf("Server replied: %s\n", buffer);

    // 6. Clean up
    close(sock);

    return 0;
}
