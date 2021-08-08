/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:56:29 by lprates           #+#    #+#             */
/*   Updated: 2021/08/08 19:24:39 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//void sendsig( int, char * );

char* stringToBinary(int pid, char* s);

int main(int argc, char *argv[])
{
    char    *str;
    int     server_pid;

    if (argc != 3)
        return (1); // placeholder for error function
    
    str = argv[2];
    server_pid = ft_atoi(argv[1]);

    ft_putstr_fd(str, 1);
    ft_putstr_fd("\n", 1);
    ft_putstr_fd(argv[1], 1);

    stringToBinary(server_pid, str);
    //sendsig(server_pid, str);
   
}
 /*
void sendsig(int pid, char *str) {

    if (!strcmp(str, "yes"))
        kill(pid, SIGUSR1);
    if (!strcmp(str, "no"))
        kill(pid, SIGUSR2);

    return ;
}*/

char* stringToBinary(int pid, char* s) {
    if(s == NULL) return 0; /* no input string */
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                kill(pid, SIGUSR1);
                usleep(100);
                strcat(binary,"1");
            } else {
                kill(pid, SIGUSR2);
                usleep(100);
                strcat(binary,"0");
            }
        }
    }
    printf("\n%s\n", binary);
    return binary;
}