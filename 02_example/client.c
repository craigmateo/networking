#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[1024] = {0};

    // 1. Create socket (Layer 4 - Transport)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // 2. Define server address (Layer 3 - Network)
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    // 3. Connect to the server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // 4. Send HTTP GET request (Layer 7 - Application)
    char *request = "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n";
    send(sock, request, strlen(request), 0);

    // 5. Receive response (Layer 7 - Application)
    read(sock, buffer, 1024);
    printf("Server response:\n%s\n", buffer);

    // 6. Close connection (Layer 5 - Session)
    close(sock);

    return 0;
}
