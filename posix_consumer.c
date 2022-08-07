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

    int shm_fd;

    void *ptr;


    // Paylasimli bellek obegi olsturulur
    shm_fd=shm_open(name,O_RDONLY,0666);

    //Paylasimli Bellek Objesinin Memory Mapi
    ptr=mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0);

    printf("%s",(char*)ptr);
    
    //Paylasilan bellegi cikar
    shm_unlink(name);
    return 0;
}
