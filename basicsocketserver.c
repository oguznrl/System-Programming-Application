#include <stdio.h>
#include <sys/types.h>  // Types used in sys/socket.h and netinet/in.h
#include <netinet/in.h> // Internet domain address structures and functions
#include <sys/socket.h> // Structures and functions used for socket API
#include <netdb.h>      // Used for domain/DNS hostname lookup
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#define MAXHOSTNAME 256

// TCP soket
int main(int argc, char const *argv[])
{
    int socketHandle;
    // Soket olusturulur

    /*
        Choose socket communications family/domain:
            Internet IPV4: AF_INET
            Internet IPV6: AF_INET6
            Unix path name (communicating processes are on the same system): AF_UNIX

        Choose socket type:
            TCP: SOCK_STREAM
            UDP: SOCK_DGRAM
            Raw protocol at network layer: SOCK_RAW

        Choose socket protocol: (See /etc/protocols)
            Internet Protocol (IP): 0 or IPPROTO_IP
            ICMP: 1
    */
    if ((socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_IP)) < 0)
    {
        close(socketHandle);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in socketInfo;
    char sysHost[MAXHOSTNAME + 1]; // Hostname of this computer we are running on
    struct hostNamePtr *hPtr;
    int portNumber = 8080;

    socketInfo.sin_family = AF_INET;
    socketInfo.sin_addr.s_addr = inet_addr("74.125.235.20"); // Use any address available to the system
    socketInfo.sin_port = htons(portNumber);        // Set port number

    bzero(&socketInfo, sizeof(struct sockaddr_in)); // Clear structure memory

    // Get system information

    gethostname(sysHost, MAXHOSTNAME);
    if (bind(socketHandle, (struct sockaddr *)&socketInfo, sizeof(struct sockaddr_in)) < 0)
    {
        close(socketHandle);
        perror("bind");
        exit(EXIT_FAILURE);
    }

    listen(socketHandle, 1);

    int socketConnection;

    if ((socketConnection = accept(socketHandle, NULL, NULL)) < 0)
    {

        exit(EXIT_FAILURE);
    }

    close(socketHandle);

    int rc = 0; // Actual number of bytes read
    char buf[512];

    rc = recv(socketConnection, buf, 512, 0);
    buf[rc] = (char)NULL; // Null terminate string

    printf("Number of bytes read: %d", rc);
    printf("Received: ", buf);
    
    return 0;
}
