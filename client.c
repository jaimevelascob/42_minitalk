/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvelasco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:36:33 by jvelasco          #+#    #+#             */
/*   Updated: 2022/04/06 21:20:35 by jvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static int msg;

void    msg_received()
{
    if (msg == 0)
    {
        printf("msg received\n");
        msg = 1;
    }
}

int main(int argc, char **argv)
{
    int         j;
    const int   server_pid = atoi(argv[1]);
    
    signal(SIGUSR1, msg_received);
    if (argc > 2)
    {
        while(*argv[2])
        { 
           j = 7;
           while (j >= 0)
           {
                if(*argv[2] & (1 << j))
                    kill(server_pid, SIGUSR2);
                else
                    kill(server_pid, SIGUSR1);
                j--; 
                usleep(80);
           }
           argv[2]++;
        }
    }
    else
        printf("wrong parametres");
}
