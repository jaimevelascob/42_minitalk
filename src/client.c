/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvelasco <jvelasco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:46:21 by jvelasco          #+#    #+#             */
/*   Updated: 2022/05/13 21:09:12 by jvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

static int	g_msg;

void	msg_received(__attribute((unused))int d)
{
	static int	x = 1;

	if (x == g_msg * 8)
	{
		ft_putstr("msg received: ");
		ft_putnbr_fd(x, 1);
		write(1, "/", 1);
		ft_putnbr_fd(g_msg * 8, 1);
		ft_putstr(" bits");
	}
	x++;
	usleep(100);
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
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			j++;
			usleep(1000);
		}
		argv[2]++;
	}
	j = 0;
	while (j < 8)
	{
		kill(server_pid, SIGUSR1);
		usleep(100);
		j++;
	}
}

int	main(int argc, char **argv)
{
	const int	server_pid = ft_atoi(argv[1]);

	signal(SIGUSR1, msg_received);
	if (argc <= 2)
		ft_putstr("need parametres");
	else if (!server_pid)
		ft_putstr("the pid has to be an integer");
	else
	{
		g_msg = ft_strlen(argv[2]);
		call(argv, server_pid);
	}
}
