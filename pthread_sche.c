#include <pthread.h>
#include <stdio.h>
#define MAX_THREAD 5

void *runner(void *ptr);

int main(int argc, char const *argv[])
{
    int i, scope;

    pthread_t pid[MAX_THREAD];
    pthread_attr_t attr;

    /* get the default attributes */
    pthread_attr_init(&attr);

    /* first inquire on the current scope */
    if (pthread_attr_getscope(&attr, &scope) != 0)
    {
        fprintf(stderr, "Unable to get scheduling scope\n");
    }
    else
    {
        if (scope == PTHREAD_SCOPE_PROCESS)
        {
            printf("PTHREAD_SCOPE_PROCESS");
        }
        else if (scope == PTHREAD_SCOPE_SYSTEM)
        {
            printf("PTHREAD_SCOPE_SYSTEM");
        }
        else
        {
            fprintf(stderr, "Illegal scope value.\n");
        }
    }

    /* set the scheduling algorithm to PCS or SCS */
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

    for (i = 0; i < MAX_THREAD; i++)
    {
        pthread_create(&pid[i], &attr, runner, NULL);
    }

    for (i = 0; i < MAX_THREAD; i++)
    {
        pthread_join(pid[i],NULL);
    }
    
    return 0;
}

void *runner(void *ptr){
    //Do somethings
    pthread_exit(0);
}
