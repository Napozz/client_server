#include <arpa/inet.h> // inet_addr()
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <stdio.h>
#define SA struct sockaddr
#define BUFFER_SIZE 80

int main(int argc, char **argv) {
    // Option for help
    char* helpOption = "-h";
    // Port past in parameter
    int port;

    if (argc != 2) {
        printf("This program takes one argument");
        printf("\nUsage: ./server <PORT>\n\n");
        return -1;
    } else if (strcmp(argv[1], helpOption) == 0) { // Display the help
        printf("\nUsage: ./server <PORT>\n\n");
        return 0;
    } else { // Else URL take the argument
        port = atoi(argv[1]);
    }

    printf("Port: %d\n", port);

    int sock, connection, len;
    struct sockaddr_in server_address, client;
    bzero(&server_address, sizeof(server_address));
    len = sizeof(client);

    // Create and verify socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Socket creation failed...\n");
        return -1;
    }

    printf("Creating server socket\n");

    // Assign IP, PORT
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    // Binding newly created socket to given IP and verification
    if ((bind(sock, (SA*)&server_address, sizeof(server_address))) != 0) {
        printf("socket bind failed...\n");
        return -1;
    }

    printf("Binding socket\n");

    // Now server is ready to listen and verification
    if ((listen(sock, 5)) != 0) {
        printf("Listen failed...\n");
        return -1;
    }

    printf("Starting listening to port: %d\n", port);

    // Accept the data packet from client and verification
    connection = accept(sock, (SA*)&client, &len);
    if (connection < 0) {
        printf("Server acceptance failed...\n");
        return -1;
    }

    // Display information
    char* clientIP = inet_ntoa(client.sin_addr);
    printf("Remote address: %s\n", clientIP);
    printf("Port: %hu\n", client.sin_port);
    // Buffer for incoming messages
    char buffer[BUFFER_SIZE];

    do {
        printf("\n——————————————————————————————————————————————————\n\n");
        // Empty buffer
        bzero(buffer, sizeof(buffer));
        // Receive client's message
        if (recv(connection, buffer, BUFFER_SIZE, 0) < 0){
            printf("Message reception failed...\n");
            return -1;
        }
        printf("Client message:\n\n%s\n", buffer);
        // Send client's message back
        if (send(connection, buffer, BUFFER_SIZE, 0) < 0){
            printf("Sending message back failed...\n");
            return -1;
        }
    } while (strcmp(buffer, "NAPOZZ") != 0);

    close(connection);
    close(sock);

    printf("\nSockets closed...\n");

    return 0;
}
