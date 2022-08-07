/* This program opens the file "in1" in the current
   directory, and prints out the return value of
   the open() system call.  If "in1" exists, open()
   will return a non-negative integer (three).  If
   "in1" does not exist, then it will return -1. */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>

int main()
{

    // open() sistem cagirisi

    // int fd;

    // fd = open("in1", O_RDONLY); // Eger dosya mevcut degilse negatif deger dondurur (3 degeri) , Neden 3 ? Her process varsayılan olarak 3 I/O akisi ile acilir
    //  0 stdin 1 stdout 2 stderr -> File Description

    // fd = open("out1", O_RDONLY);// Hata verir cunku boyle bir dosya yok

    /*fd = open("out1", O_WRONLY | O_CREAT | O_TRUNC, 0644); // O_CREAT-> Eger dosya yoksa olusturur -- O_TRUNC->Eger dosya mevcutsa truncate eder (0 byte yapar)

    if (fd < 0)
    {
        perror("File Not Found");
        exit(1);
    }
    else
    {
        printf("%d\n", fd);
    }*/

    // close() sistem cagirisi

    /* This program opens and closes the file "in1" in
       a variety of ways.  Make sure you understand
       this program, especially the return values of the
       open calls. */

    /*int fd1, fd2;

    fd1 = open("in1", O_RDONLY);
    if (fd1 < 0)
    {
        perror("c1");
        exit(1);
    }

    fd2 = open("in1", O_RDONLY);
    if (fd2 < 0)
    {
        perror("c1");
        exit(1);
    }

    printf("in1 dosyasi iki kez acildi :  Fd'ler %d ve %d\n", fd1, fd2);

    if (close(fd1) < 0)
    {
        perror("c1");
        exit(1);
    }
    if (close(fd2) < 0)
    {
        perror("c1");
        exit(1);
    }

    printf("Her ikiside kapandi fd's\n");

    fd2 = open("in1", O_RDONLY);
    if (fd2 < 0)
    {
        perror("c1");
        exit(1);
    }

    printf("in1 fd2 icersinde tekrardan acildi: %d\n", fd2);

    if (close(fd2) < 0)
    {
        perror("c1");
        exit(1);
    }

    printf("fd2 kapatildi. Simdi close(fd2) tekrar cagirilacak\n");
    printf("Bu hataya sebep olmasi lazim.\n\n");

    if (close(fd2) < 0)
    {
        perror("c1");
        exit(1);
    }*/

    // read() sistem cagirisi
    /*
    char *c;
    int fd_r, sz;
    c = (char *)calloc(100, sizeof(char));
    fd_r = open("in1", O_RDONLY);
    if (fd_r < 0)
    {
        perror("r1");
        exit(1);
    }

    sz = read(fd_r, c, 10);
    printf("read(%d, c, 10) cagirildi. Okunan %d byte okundu.\n",
           fd_r, sz);
    c[sz] = '\0';
    printf("Okunan byte lar: %s\n", c);

    sz = read(fd_r, c, 99);
    printf("read(%d, c, 99) cagirildi. Okunan %d byte okundu.\n",
           fd_r, sz);
    c[sz] = '\0';
    printf("Okunan byte lar: %s\n", c);
    */

    // write() sistem cagrisi

    /*int fd_w, sz;

    fd_w = open("out3", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_w < 0)
    {
        perror("r1");
        exit(1);
    }

    sz = write(fd_w, "cs360\n", strlen("cs360\n"));

    printf("write(%d, \"cs360\\n\", %d) cagirldi. %d dondurecek\n",
           fd_w, strlen("cs360\n"), sz);

    close(fd_w);*/

    char *c;
    int fd, sz, i;

    c = (char *)calloc(100, sizeof(char));
    fd = open("in1", O_RDONLY);
    if (fd < 0)
    {
        perror("r1");
        exit(1);
    }

    sz = read(fd, c, 10);
    printf("We have opened in1, and called read(%d, c, 10).\n", fd);
    printf("It returned that %d bytes  were read.\n", sz);
    c[sz] = '\0';
    printf("Those bytes are as follows: %s\n", c);

    i = lseek(fd, 0, SEEK_CUR);
    printf("lseek(%d, 0, SEEK_CUR) returns that the current offset of the file is %d\n\n", fd, i);

    printf("now, we seek to the beginning of the file and call read(%d, c, 10)\n",
           fd);
    lseek(fd, 0, SEEK_SET);
    sz = read(fd, c, 10);
    c[sz] = '\0';
    printf("The read returns the following bytes: %s\n", c);

    printf("now, we do lseek(%d, -6, SEEK_END).  It returns %d\n",
           fd, lseek(fd, -6, SEEK_END));
    printf("If we do read(%d, c, 10), we get the following bytes: ", fd);

    sz = read(fd, c, 10);
    c[sz] = '\0';
    printf("%s\n", c);

    printf("Finally, we do lseek(%d, -1, SEEK_SET).  This returns -1.\n", fd);
    printf("perror() tells us why: ");
    fflush(stdout);

    i = lseek(fd, -1, SEEK_SET);
    perror("l1");

    return 0;
}