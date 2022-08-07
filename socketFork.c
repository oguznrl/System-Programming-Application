#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <netinet/in.h>
#define MAXHOSTNAME 256

// Catch signals from child processes
void handleSig(int signum)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

int main(int argc, char const *argv[])
{
    struct sockaddr_in socketInfo;
    char sysHost[MAXHOSTNAME + 1]; // Hostname of this computer we are running on
    struct hostNamePtr *hPtr;
    int portNumber = 8080;
    int socketHandle;

    signal(SIGCHLD, handleSig);

    bzero(&socketInfo, sizeof(struct sockaddr_in));

    gethostname(sysHost, MAXHOSTNAME);

    if ((hPtr = gethostbyname(sysHost)) == NULL)
    {
        printf("System hostname misconfigured.");
        exit(EXIT_FAILURE);
    }

    if ((socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0)
    {
        close(socketHandle);
        exit(EXIT_FAILURE);
    }

    // Load system information into socket data structures

    socketInfo.sin_family = AF_INET;
    socketInfo.sin_addr.s_addr = htonl(INADDR_ANY); // Use any address available to the system
    socketInfo.sin_port = htons(portNumber);        // Set port number

    // Bind the socket to a local socket address
    if (bind(socketHandle, (struct sockaddr *)&socketInfo, sizeof(struct sockaddr_in)) < 0)
    {
        close(socketHandle);
        perror("Binding error");
        exit(EXIT_FAILURE);
    }

    listen(socketHandle, 1);

    int socketConnection;

    while (1)
    {
        if ((socketConnection = accept(socketHandle, NULL, NULL) < 0))
        {
            close(socketHandle);
            if (errno == EINTR)
                continue;
            perror("accept");
            exit(EXIT_FAILURE);
        }
        switch (fork())
        {
        case -1:
            perror("fork");
            close(socketHandle);
            close(socketConnection);
            exit(EXIT_FAILURE);
            break;
        case 0: // Child process - do stuff
            close(socketHandle);
            // Do your server stuff like read/write messages to the socket here!
            exit(0);
            break;
        default: // Parent process, look for another connection
            close(socketConnection);
            break;
        }
    }

    return 0;
}
