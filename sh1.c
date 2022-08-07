#include <signal.h>
#include <stdio.h>
void cntl_c_handler(int dummy)
{
    printf("Gapatamazsın evladım\n");
    signal(SIGINT, cntl_c_handler);
}

void sigquit_handler(int dummy)
{
    printf("Çıkamazsın evladım\n");
    signal(SIGQUIT, sigquit_handler);
}

int main(int argc, char const *argv[])
{
    int i, j;

    signal(SIGINT, cntl_c_handler);

    signal(SIGQUIT, sigquit_handler);

    for (j = 0; j < 200; j++)
    {
        for (i = 0; i < 100000000; i++)
            ;
    }
}
