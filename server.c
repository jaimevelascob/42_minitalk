#include <stdio.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <signal.h>

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char*   my_strcat(char *str, char c)
{
    char    *cpy;

    cpy = malloc(sizeof(char)*ft_strlen(str)+2);
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

void	ft_putstr(char *str)
{
	int		count;

	count = 0;
	while (str[count] != '\0')
	{
		write(1, &str[count], 1);
		count++;
	}
    write(1,"\n",1);
}


void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	x;
    static char *str;
	static int	j = 0;
    
	(void)(ucontext);
	if (!str)
        str = calloc(1, 1);
    if (sig == SIGUSR2)
        x = x | (1 << j);
    j++;
	if (j == 8)
	{
        if (x == 0)
        { 
            ft_putstr(str);
            free(str);
            str = 0;
        }
        else
            str = my_strcat(str, x);
        j = 0;
        x = 0;
	}
	kill(info->si_pid, SIGUSR1);
    
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	printf("PID -> %d\n", getpid());
	printf("Server connecting...\n");
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
}
