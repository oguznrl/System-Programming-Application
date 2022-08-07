#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <unistd.h>

/*
CH3-Process
*/
int main(int argc, char const *argv[])
{
    // Paylasilan bellek icin ayilan boyut(byte)
    const int SIZE = 4096;
    // Paylasilcak bellegin ismi
    const char *name = "OS";
    // Bellege yazilacak veri
    const char *message_0 = "Hello";
    const char *message_1 = "World !!!";

    //shared memory file description
    int shm_fd;

    void *ptr;

    // Paylasimli bellek obegi olsturulur
    shm_fd=shm_open(name,O_CREAT|O_RDWR,0666);

    //Paylasimli bellegin boyutunun ayarları
    ftruncate(shm_fd,SIZE);

    //Paylasimli Bellek Objesinin Memory Mapi
    ptr=mmap(0,SIZE,PROT_WRITE,MAP_SHARED,shm_fd,0);

    //Paylasilan Bellege Verileri Yaz
    sprintf(ptr,"%s",message_0);
    ptr+=strlen(message_0);
    sprintf(ptr,"%s",message_1);
    ptr+=strlen(message_1);

    return 0;
}
