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
#include <stdlib.h>
#include <signal.h>

char* stringToBinary(char* s) {
    if(s == NULL) return 0;
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1);
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) for(int j = 7; j >= 0; --j)
    {
            if(s[i] & (1 << j)) 
                strcat(binary,"1");
             else 
                strcat(binary,"0");
    }
    return binary;
}

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        char *c = stringToBinary(argv[2]);
        int len = strlen(c);
        int i = 0;
        while(i < len)
        {  
            if(c[i] == '0')
                kill(atoi(argv[1]),SIGUSR1);
            if(c[i] == '1')
                kill(atoi(argv[1]),SIGUSR2);
            printf("%c", c[i]);
            i++;
            usleep(80);
        }
    }
    else
        printf("wrong parametres");
}
