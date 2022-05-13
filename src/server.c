/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvelasco <jvelasco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:46:28 by jvelasco          #+#    #+#             */
/*   Updated: 2022/05/13 21:09:10 by jvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

void	handler(int sig, siginfo_t *info, void *ucontext)
{
	static char	x;
	static char	*str;
	static int	j;

	(void)(ucontext);
	if (!str)
		str = ft_calloc(1, 1);
	if (sig == SIGUSR2)
		x = x | (1 << j);
	j++;
	if (j == 8)
	{
		if (x == 0)
		{
			ft_putstr(str);
			write(1, "\n", 1);
			free(str);
			str = 0;
		}
		else
			str = ft_strcat(str, x);
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
