#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
   struct sockaddr_in remoteSocketInfo;
   struct hostent *hPtr;
   int socketHandle;
   const char *remoteHost="localhost";
   int portNumber = 8080;

   bzero(&remoteSocketInfo, sizeof(struct sockaddr_in));  // Clear structure memory

   // Get system information

   if((hPtr = gethostbyname(remoteHost)) == NULL)
   {
      printf("System DNS name resolution not configured properly." );
      printf("Error number: %d",ECONNREFUSED);
      exit(EXIT_FAILURE);
   }

   // create socket

   if((socketHandle = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
      close(socketHandle);
      exit(EXIT_FAILURE);
   }

   // Load system information into socket data structures

   memcpy((char *)&remoteSocketInfo.sin_addr, hPtr->h_addr, hPtr->h_length);
   remoteSocketInfo.sin_family = AF_INET;
   remoteSocketInfo.sin_port = htons((u_short)portNumber);      // Set port number

   if(connect(socketHandle, (struct sockaddr *)&remoteSocketInfo, sizeof(struct sockaddr_in)) < 0)
   {
      close(socketHandle);
      exit(EXIT_FAILURE);
   }

   int rc = 0;  // Actual number of bytes read by function read()
   char buf[512];
   
   strcpy(buf,"Message to send");
   send(socketHandle, buf, strlen(buf)+1, 0);
}

