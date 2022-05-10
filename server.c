#include <stdio.h> 
#include <unistd.h> 
#include <signal.h>

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	x;
	static int	j = 7;

	(void)(ucontext);
	if (sig == SIGUSR2)
		x = x | (1 << j);
	if (j == 0)
	{
		write(1, &x, 1);
		x = 0;
		j = 7;
	}
	else
		j--;
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	printf("%d\n", getpid());
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
}
