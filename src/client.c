/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvelasco <jvelasco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:46:21 by jvelasco          #+#    #+#             */
/*   Updated: 2022/05/25 17:51:23 by jvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/server.h"

static int	g_msg;

void	msg_received(__attribute((unused))int d)
{
	g_msg = 1;
}

void	ft_print_msg(int size, int val)
{
	ft_putstr("msg received: ");
	ft_putnbr_fd(val, 1);
	write(1, "/", 1);
	ft_putnbr_fd(size, 1);
	ft_putstr(" bits");
}

int	send_bit(char **argv, int bit, int server_pid)
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
			while (g_msg == 0)
			{
				bit++;
				pause();
			}
			g_msg = 0;
		}
		argv[2]++;
	}
	return (bit);
}

void	call(char **argv, int server_pid)
{
	int			j;
	const int	size = ft_strlen(argv[2]) * 8;
	static int	bit;

	bit = send_bit(argv, bit, server_pid);
	j = 0;
	while (j < 8)
	{
		kill(server_pid, SIGUSR1);
		usleep(100);
		j++;
	}
	ft_print_msg(size, bit);
}

int	main(int argc, char **argv)
{
	const int	server_pid = ft_atoi(argv[1]);

	signal(SIGUSR1, msg_received);
	if (argc <= 2)
		ft_putstr("need parametres");
	else if (!server_pid)
		ft_putstr("the pid has to be an integer");
	else if (*argv[2] != 0)
		call(argv, server_pid);
	else
		ft_putstr("wrong parametres");
}
