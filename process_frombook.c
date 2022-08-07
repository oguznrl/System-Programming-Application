#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/wait.h> 
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        printf("Process olusuturulamadi");
        return -1;
    }
    else if (pid == 0)
    {  // Child Process

        /*  Execute FILE, searching in the `PATH' environment variable if
            it contains no slashes, with all arguments after FILE until a
            NULL pointer and environment from `environ'.  */
        execlp("bin/ls", "ls", NULL);//Like all of the exec functions, execlp replaces the calling process image with a new process image. This has the effect of running a new program with the process ID of the calling process. Note that a new process is not started; the new process image simply overlays the original process image. 
        
        return 0;
    }
    else
    {
        // Parent process child processi beklemekte
        wait(NULL);
        printf("Child tamamlandi");
    }

    return 0;
}
