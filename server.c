#include <stdio.h> 
#include <unistd.h> 
#include <string.h>
#include <signal.h>

char*   my_strcat(char *str, char c)
{
    char    *cpy;

    cpy = malloc(sizeof(char)*strlen(str)+2);
    int i = 0;
    while(str[i])
    {
        cpy[i] = str[i];
        i++;
    }
    cpy[i++] = c;
    cpy[i] = '\0';
    free(str);
    return cpy; 
}

void    ft_binarytochar(char *str)
{
    char    x;

    //no intentes recordar, recrea, no pretendo decir que t engas que hacerlo todo de zero, ya que eso implicaria reinventar todas la herramientas
    //por eso es importante que veas a otras personas usar la herramientas, pero luego tienes que saber como usarlas
    int i = 0;
    int j = 7;
    x = 0;
    while(i < 8)
    {
        if(str[i] == '1')
            x = x | (1 << j);
        i++;
        j--;
    }
    printf("%c\n", x);
}
void    handler(int sig, siginfo_t *info, void *ucontext)
{
    static char *str;
    int bitcount;
   
    if (!str)
    {
        str = calloc(1, 1);
        bitcount = 0;
    }
    bitcount++;
    if (sig == SIGUSR1)
        str = my_strcat(str, '0');
    else    
        str = my_strcat(str, '1');
    printf("%s\n", str);
    if (bitcount == 8)
    {
        ft_binarytochar(str); 
        free(str);
        str = 0;
    }
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
