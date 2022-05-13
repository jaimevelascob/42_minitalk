/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvelasco <jvelasco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:46:06 by jvelasco          #+#    #+#             */
/*   Updated: 2022/05/13 21:02:07 by jvelasco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr(char *str);
char	*ft_strcat(char *str, char c);
void	*ft_calloc(size_t count, size_t size);
#endif
