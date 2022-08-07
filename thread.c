#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void *print_message_function( void *ptr );

int main(int argc, char const *argv[])
{
	pthread_t thread1,thread2;

	const char *message1 = "Thread 1";
	const char *message2 = "Thread 2";

	int  iret1, iret2;
	iret1=pthread_create( &thread1, NULL, print_message_function, (void*) message1);
	if(iret1){
		fprintf(stderr,"Thread olusturulurken hata gerceklesti, hata kodu: %d\n",iret1);
        exit(EXIT_FAILURE);
	}
	
	iret2=pthread_create( &thread2, NULL, print_message_function, (void*) message2);
	if(iret2){
		fprintf(stderr,"Thread olusturulurken hata gerceklesti, hata kodu: %d\n",iret2);
        exit(EXIT_FAILURE);
	}
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return 0;
}

void *print_message_function( void *ptr ){
    
	char *message;
    message = (char *) ptr;
    printf("%s \n", message);

}
