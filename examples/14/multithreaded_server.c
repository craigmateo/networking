/*
 * Filename: multithreaded_server.c
 * Summary: 
 * This example demonstrates multithreading concepts in a client-server program.
 * The server accepts multiple client connections and handles each client in a separate thread,
 * allowing concurrent processing of multiple clients.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 5

// Thread function to handle client communication
void *handle_client(void *client_socket_ptr) {
    int client_socket = *(int *)client_socket_ptr;
    free(client_socket_ptr);

    char buffer[1024] = {0};
    int bytes_read;

    printf("Client connected. Thread ID: %ld\n", pthread_self());

    // Echo loop: receive data and send it back to client
    while ((bytes_read = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Received from client: %s\n", buffer);
        write(client_socket, buffer, bytes_read);
    }

    printf("Client disconnected. Thread ID: %ld\n", pthread_self());
    close(client_socket);
    pthread_exit(NULL);
}

int main() {
    int server_fd, *new_sock;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    pthread_t thread_id;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Bind to the port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  // Bind to all interfaces
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);

    // Accept clients and create threads
    while (1) {
        new_sock = malloc(sizeof(int));
        if (!new_sock) {
            perror("Malloc failed");
            continue;
        }

        *new_sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (*new_sock < 0) {
            perror("Accept failed");
            free(new_sock);
            continue;
        }

        // Create a thread to handle the client
        if (pthread_create(&thread_id, NULL, handle_client, (void *)new_sock) != 0) {
            perror("Thread creation failed");
            free(new_sock);
            continue;
        }

        // Detach thread so resources are freed when it finishes
        pthread_detach(thread_id);
    }

    close(server_fd);
    return 0;
}
