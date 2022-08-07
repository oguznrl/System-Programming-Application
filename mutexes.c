#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *increaseCounter(void *ptr);
int counter=0;

int main(){
    pthread_t thread1,thread2;

    const char *message1 = "Thread 1";
	const char *message2 = "Thread 2";
	
    int  iret1, iret2;
	iret1=pthread_create( &thread1, NULL, increaseCounter, (void *)message1);
	if(iret1){
		fprintf(stderr,"Thread olusturulurken hata gerceklesti, hata kodu: %d\n",iret1);
        exit(EXIT_FAILURE);
	}
	
	iret2=pthread_create( &thread2, NULL, increaseCounter, (void *)message2);
	if(iret2){
		fprintf(stderr,"Thread olusturulurken hata gerceklesti, hata kodu: %d\n",iret2);
        exit(EXIT_FAILURE);
	}
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);

    return 0;
}

void *increaseCounter(void *ptr){
    pthread_mutex_lock(&mutex);
    char *message;
    message = (char *) ptr;
    counter++;
    printf("%s %d\n",message,counter);
    pthread_mutex_unlock(&mutex);

}