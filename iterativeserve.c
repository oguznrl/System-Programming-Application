#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#define MAXHOSTNAME 256

void doit(int fd);

int main(int argc, char const **argv)
{
    struct sockaddr_in socketInfo;
    char *sysHost; // Hostname of this computer we are running on
    struct hostent *hPtr;
    int socketHandle;
    int portNumber = atoi(argv[2]);
    bzero(&socketInfo, sizeof(struct sockaddr_in)); // Clear structure memory

    if (argc != 3)
    {
        fprintf(stderr, "usage: serve1 hostname port\n");
        exit(1);
    }

    sysHost = argv[1];
    if (portNumber < 5000)
    {
        fprintf(stderr, "usage: serve1 hostname port\n");
        fprintf(stderr, "       port must be > 5000\n");
        exit(1);
    }

    // Get system information

    gethostname(sysHost, MAXHOSTNAME); // Get the name of this computer we are running on
    if ((hPtr = gethostbyname(sysHost)) == NULL)
    {
        printf("System hostname misconfigured.");
        exit(EXIT_FAILURE);
    }

    // create socket

    if ((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        close(socketHandle);
        exit(EXIT_FAILURE);
    }

    // Load system information into socket data structures

    socketInfo.sin_family = AF_INET;
    socketInfo.sin_addr.s_addr = htonl(INADDR_ANY); // Use any address available to the system
    socketInfo.sin_port = htons(portNumber);        // Set port number

    // Bind the socket to a local socket address

    if (bind(socketHandle, (struct sockaddr *)&socketInfo, sizeof(socketInfo)) < 0)
    {
        close(socketHandle);
        perror("bind");
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        if (listen(socketHandle, 1) == -1)
        {
            perror("listen()");
            exit(1);
        }

        int socketConnection;
        if ((socketConnection = accept(socketHandle, NULL, NULL)) < 0)
        {   
            perror("accept()");
            exit(EXIT_FAILURE);
        }
        printf("received a client connection on %d\n", socketConnection);
        doit(socketConnection);
        close(socketConnection);
    }

    return 0;
}

void doit(int fd)
{
    int saved_stdin, saved_stdout;

    saved_stdin = dup(0);
    saved_stdout = dup(1);

    dup2(fd, 0);
    dup2(fd, 1);
    system("/blugreen/homes/plank/bin/SUN4/pty -ne /usr/games/arithmetic");
    dup2(saved_stdin, 0);
    dup2(saved_stdout, 1);
    close(saved_stdin);
    close(saved_stdout);
    printf("client connection %d finished\n", fd);
}