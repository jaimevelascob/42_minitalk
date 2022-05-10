/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvelasco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:36:33 by jvelasco          #+#    #+#             */
/*   Updated: 2022/05/10 21:42:21 by jvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int			ft_atoi(const char *str);
int			ft_strlen(const char *s);
static int	g_msg;

void	msg_received()
{
	static int	x = 1;

	if (x == g_msg * 8)
		printf("msg received %d/%d\n", x, g_msg * 8);
	x++;
	usleep(50);
}

void	call(char **argv, int server_pid)
{
	int	j;

	while (*argv[2])
	{
		j = 0;
		while (j < 8)
		{
			if (*argv[2] & (1 << j))
			{
				kill(server_pid, SIGUSR2);
				write(1,"1",1);
			}
			else
			{
				kill(server_pid, SIGUSR1);
				write(1,"0",1);
			}
			printf("\nj: %d\n", j);
			j++;
			usleep(180);
		}
		argv[2]++;
	}
	j = 0;
	while (j < 8)
	{
		kill(server_pid, SIGUSR1);
		usleep(180);
		j++;
		printf("%d\n",j);
		write(1, "\n", 1);
	}
}

int	main(int argc, char **argv)
{
	const int	server_pid = ft_atoi(argv[1]);

	signal(SIGUSR1, msg_received);
	if (argc <= 2)
		printf("need parametres");
	else if (server_pid == 0 || (kill(server_pid, SIGUSR1) == -1
			&& kill(server_pid, SIGUSR2) == -1))
		printf("pid dosnt exist");
	else
	{
		g_msg = ft_strlen(argv[2]);
		call(argv, server_pid);
	}
}
