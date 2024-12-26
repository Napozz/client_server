#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

/**
 * This method is the help of the program, it displays how to use the program.
 */
void help(void) {
    printf("───▄▀▀▀▄▄▄▄▄▄▄▀▀▀▄───\n"
           "───█▒▒░░░░░░░░░▒▒█───\n"
           "────█░░█░░░░░█░░█────\n"
           "─▄▄──█░░░▀█▀░░░█──▄▄─\n"
           "█░░█─▀▄░░░░░░░▄▀─█░░█\n"
           "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█\n"
           "█░░╦─╦╔╗╦─╔╗╔╗╔╦╗╔╗░░█\n"
           "█░░║║║╠─║─║─║║║║║╠─░░█\n"
           "█░░╚╩╝╚╝╚╝╚╝╚╝╩─╩╚╝░░█\n\n");
    printf("Welcome on the program myhost which allows you to find the ip address of the host you past in"
           " argument no matter if this ipv4 or ipv6.\n\n");
    printf("Usage: \n");
    printf("./myhost hostname\n");
    printf("For example:\n");
    printf("./myhost google.fr\n\n");
    printf("Option: \n");
    printf("-h\tDisplay the help\n\n\n");
}

/**
 * Entry point of the program.
 * @param argc Number of argument.
 * @param argv The list of argument.
 * @return 0 if everything went well, -1 else.
 */
int main(int argc, char **argv) {
    // URL past in parameter
    char* url;
    // Option for help
    char* helpOption = "-h";
    // If there is no argument, display an error message and the help
    if (argc != 2) {
        printf("                                                                                        \n"
               "                                                                                        \n"
               "                ░░░░                                                                    \n"
               "                                                                                        \n"
               "                                            ██                                          \n"
               "                                          ██░░██                                        \n"
               "  ░░          ░░                        ██░░░░░░██                            ░░░░      \n"
               "                                      ██░░░░░░░░░░██                                    \n"
               "                                      ██░░░░░░░░░░██                                    \n"
               "                                    ██░░░░░░░░░░░░░░██                                  \n"
               "                                  ██░░░░░░██████░░░░░░██                                \n"
               "                                  ██░░░░░░██████░░░░░░██                                \n"
               "                                ██░░░░░░░░██████░░░░░░░░██                              \n"
               "                                ██░░░░░░░░██████░░░░░░░░██                              \n"
               "                              ██░░░░░░░░░░██████░░░░░░░░░░██                            \n"
               "                            ██░░░░░░░░░░░░██████░░░░░░░░░░░░██                          \n"
               "                            ██░░░░░░░░░░░░██████░░░░░░░░░░░░██                          \n"
               "                          ██░░░░░░░░░░░░░░██████░░░░░░░░░░░░░░██                        \n"
               "                          ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                        \n"
               "                        ██░░░░░░░░░░░░░░░░██████░░░░░░░░░░░░░░░░██                      \n"
               "                        ██░░░░░░░░░░░░░░░░██████░░░░░░░░░░░░░░░░██                      \n"
               "                      ██░░░░░░░░░░░░░░░░░░██████░░░░░░░░░░░░░░░░░░██                    \n"
               "        ░░            ██░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░██                    \n"
               "                        ██████████████████████████████████████████                      \n"
               "                                                                                        \n"
               "                                                                                        \n"
               "                                                                                        \n"
               "                                                                                        \n"
               "                  ░░                                                                    \n");
        printf("##################################################################################\n");
        printf("################### The program should take one url as argument! #################\n");
        printf("##################################################################################\n\n\n");
        help();
        return -1;
    } else if (strcmp(argv[1], helpOption) == 0) { // Display the help
        help();
        return 0;
    } else { // Else URL take the argument
        url = argv[1];
    }

    // Structure which will contains the information
    struct hostent *host_info;

    // check that the host exists
    if((host_info=gethostbyname(url)) == NULL) {
        printf("##################################################################################\n");
        printf("######################### The hostname given doesn't exist! ######################\n");
        printf("##################################################################################\n\n\n");
        help();
        return -1;
    }

    // Search for the ip address and display it with the hostname
    printf("%s has the ip address: %s\n", host_info->h_name, inet_ntoa(*((struct in_addr *)host_info->h_addr)));

    return 0;
}
