#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define MAXHOSTNAME 256

int main(int argc, char const *argv[])
{
    struct sockaddr_in socketInfo;
    char sysHost[MAXHOSTNAME + 1],buf[100]; // Hostname of this computer we are running on
    struct hostent *hPtr;
    int socketHandle;
    int portNumber = 8080;
    fd_set readfds, masterfds;
    int nopen, n;
    bzero(&socketInfo, sizeof(struct sockaddr_in)); // Clear structure memory

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

    if (connect(socketHandle, (struct sockaddr *)&socketInfo, sizeof(struct sockaddr_in)) < 0)
    {
        close(socketHandle);
        exit(EXIT_FAILURE);
    }

    FD_ZERO(&masterfds);
    FD_SET(0, &masterfds);
    FD_SET(socketHandle, &masterfds);

    while (1)
    {
        memcpy(&readfds, &masterfds, sizeof(fd_set));
        if (select(socketHandle + 1, &readfds, NULL, NULL, NULL) < 0)
        {
            perror("on select");
            exit(1);
        }
        if (FD_ISSET(0, &readfds))
        {
            n = read(0, buf, 100);
            if (n == 0)
            {
                close(0);
                close(socketHandle);
                exit(1);
            }
            else
            {
                write(socketHandle, buf, n);
            }
        }
        else if (FD_ISSET(socketHandle, &readfds))
        {
            n = read(socketHandle, buf, 100);
            if (n == 0)
            {
                close(0);
                close(socketHandle);
                exit(1);
            }
            else
            {
                write(1, buf, n);
            }
        }
    }

    return 0;
}
