/*
 * Summary:
 * This simple C program demonstrates the concept of transport layer port addressing
 * by simulating a client-server interaction. The server listens on a well-known port (80),
 * while the client selects a random source port from the dynamic/private range.
 * The program prints out the source and destination port numbers used in the communication,
 * illustrating how port numbers uniquely identify applications during transport layer communication.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define well-known server port (HTTP)
#define SERVER_PORT 80

// Dynamic/private port range for client
#define DYNAMIC_PORT_START 49152
#define DYNAMIC_PORT_END 65535

int main() {
    srand(time(NULL));

    // Simulate client choosing a random dynamic source port
    int client_source_port = DYNAMIC_PORT_START + rand() % (DYNAMIC_PORT_END - DYNAMIC_PORT_START + 1);

    // Server port is fixed (well-known port)
    int server_dest_port = SERVER_PORT;

    printf("Client source port (random dynamic): %d\n", client_source_port);
    printf("Server destination port (well-known): %d\n", server_dest_port);

    printf("\nSimulating a request from client to server...\n");
    printf("Sending data from %d (client) to %d (server)...\n", client_source_port, server_dest_port);

    // Simulate server response where ports switch roles
    printf("\nSimulating server response back to client...\n");
    printf("Sending data from %d (server) to %d (client)...\n", server_dest_port, client_source_port);

    return 0;
}
