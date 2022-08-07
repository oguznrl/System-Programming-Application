#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

#define COUNT_DONE 10
#define COUNT_HALT1 3
#define COUNT_HALT2 6
int counter = 0;
void *function1(void *ptr);
void *function2(void *ptr);
int main()
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, function1, NULL);
    pthread_create(&thread2, NULL, function2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final count: %d\n", counter);

    exit(EXIT_SUCCESS);
}

// Write numbers 1-3 and 8-10 as permitted by function2()
void *function1(void *ptr)
{
    while (1)
    {
        // Lock mutex and then wait for signal to relase mutex
        pthread_mutex_lock(&count_mutex);

        // Wait while function2() operates on count
        // mutex unlocked if condition varialbe in function2() signaled.
        pthread_cond_wait(&condition_var, &count_mutex);

        counter++;

        printf("Counter value function1: %d\n", counter);
        pthread_mutex_unlock(&count_mutex);

        if (counter >= COUNT_DONE)
            return (NULL);
    }
}

void *function2(void *ptr)
{
    while (1)
    {
        // Lock mutex and then wait for signal to relase mutex
        pthread_mutex_lock(&count_mutex);

        if (counter < COUNT_HALT1 || counter > COUNT_HALT2)
        {
            // Condition of if statement has been met.
            // Signal to free waiting thread by freeing the mutex.
            // Note: function1() is now permitted to modify "count".
            pthread_cond_signal(&condition_var);
        }
        else
        {
            counter++;
            printf("Counter value function2: %d\n", counter);
        }
        pthread_mutex_unlock(&count_mutex);

        if (counter >= COUNT_DONE)
            return (NULL);
    }
}