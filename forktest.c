#include <stdio.h>
// Required by for routine
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h> // Declaration for exit()

int globalVariable = 2;

int main(int argc, char const *argv[])
{
    char sIdentifier[50]="";
    int iStackVariable = 20;
    pid_t PID = fork();
    if (PID == 0)
    {
        strcpy(sIdentifier,"Child Process");
        globalVariable++;

        iStackVariable++;
    }
    else if (PID < 0)            // failed to fork
    {

        printf("Failed to fork");

        exit(1);
    }
    else
    {
        strcpy(sIdentifier,"Parent Process");
    }
    printf("%s \nGlobal Var: %d \nStack Var: %d\n-----\n",sIdentifier,globalVariable,iStackVariable);

    return 0;
}
