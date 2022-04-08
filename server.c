#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <signal.h>
#include <stdlib.h>

int j = 7; // variable para mover byte

//no intentes recordar, recrea, no pretendo decir que t engas que hacerlo todo de zero, ya que eso implicaria reinventar todas la herramientas
//por eso es importante que veas a otras personas usar la herramientas, pero luego tienes que saber como usarlas

void    handler(int sig, siginfo_t *info, void *ucontext)
{
    static char x;

    if (sig == SIGUSR2)
        x = x | (1 << j);
    if (j == 0)
    {
        write(1, &x, 1);
        kill(info->si_pid, SIGUSR1);
        x = 0;
        j = 7;
    }
    else
        j--;
    usleep(70);
}


int main(void)
{
    struct sigaction sa;

    sa.sa_sigaction = handler;
    sa.sa_flags = SA_SIGINFO;
    printf("%d\n", getpid());
    sigaction(SIGUSR1, &sa, 0);
    sigaction(SIGUSR2, &sa, 0);
    while(1)
        pause();
}
