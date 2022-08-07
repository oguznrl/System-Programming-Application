#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#define NTHREADS 10
int counter=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *increaseCounter(void *ptr);

int main(){
    pthread_t threads_id[NTHREADS];
    
    //Thread Created
    for (int i = 0; i < NTHREADS; i++)
    {
        pthread_create(&threads_id[i],NULL,increaseCounter,NULL);
    }
    //Thread Joined
    for (int i = 0; i < NTHREADS; i++)
    {
        pthread_join(threads_id[i],NULL);
    }
    return 0;
}

void *increaseCounter(void *ptr){
    printf("Thread number %ld\n", pthread_self());
    pthread_mutex_lock(&mutex);
    counter++;
    printf("Counter %d\n",counter);
    pthread_mutex_unlock(&mutex);

}