#include <stdio.h> 
#include <unistd.h> 
#include <signal.h>

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	x;
	static int	j = 0;

	// hacer un str e ir haciendo append para luego printear el str
	(void)(ucontext);
	if (sig == SIGUSR1)
		write(1, "0\n", 2);
	if (sig == SIGUSR2)
	{
		write(1, "1\n", 2);
		x = x | (1 << j);
	}
	j++;
	if (j == 8)
	{
		write(1, &x, 1);
		x = 0;
		j = 0;
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
