#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#include <stdio.h>
#define SA struct sockaddr

int main(int argc, char **argv) {
    // Option for help
    char* helpOption = "-h";
    // URL past in parameter
    char* url;
    // Port past in parameter
    char* chr_port;
    int port;

    if (argc != 2) {
        printf("This program takes one argument with the format URL:PORT");
        printf("\nUsage: ./client <URL:PORT>\n");
        return -1;
    } else if (strcmp(argv[1], helpOption) == 0) { // Display the help
        printf("\nUsage: ./client <URL:PORT>\n\n");
        return 0;
    } else { // Else URL take the argument
        url = strtok(argv[1], ":");
        chr_port = strtok(NULL, ":");
        port = atoi(chr_port);
    }

    printf("\nHost: %s\n", url);
    printf("Port: %d\n", port);

    // Structure which will contains the information
    struct hostent *host_info;
    // Check that the host exists
    if((host_info=gethostbyname(url)) == NULL) {
        printf("The hostname given doesn't exist!\n");
        return -1;
    }
    // Find IP address
    char* ipAddress = inet_ntoa(*((struct in_addr *)host_info->h_addr));

    int sock;
    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));

    // Socket create and verification
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Socket creation failed...\n");
        return -1;
    }

    // Assign IP and PORT
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(ipAddress);
    server_address.sin_port = htons(port);

    // Connect the client socket to server socket
    if (connect(sock, (SA*)&server_address, sizeof(server_address)) != 0) {
        printf("Connection with the server failed...\n");
        return -1;
    }

    printf("Address IP: %s\n", ipAddress);
    printf("\nConnected\n");

    // Ask for the command
    for (;;) {
        printf("\n——————————————————————————————————————————————————\n\n");
        printf("\nPlease enter your command to send to the server: ");
        char command[80];
        scanf("%s",command);

        write(sock, command, sizeof(command));

        // Prepare the response
        char response[255];
        bzero(response, sizeof(response));
        // Get the response
        read(sock, response, sizeof(response));

        printf("\nServer response:\n\n%s\n", response);

        if (strcmp(command, "NAPOZZ") == 0) break;
    }

    // Close the socket
    close(sock);

    printf("\n\nSocket closed...\n");

    return 0;
}
