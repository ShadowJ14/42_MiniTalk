/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:56:29 by lprates           #+#    #+#             */
/*   Updated: 2021/09/04 04:10:52 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	check_pid(const char *str)
{
	while (*str && ft_isdigit(*str))
		str++;
	return (!*str);
}

static void receive_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("Wrong signal received. Exiting.", 1);
		exit(4);
	}
	return ;
}

int	main(int argc, char *argv[])
{
	int		server_pid;

	if (argc != 3)
		return (1);
	if (!check_pid(argv[1]))
		return (2);
	server_pid = ft_atoi(argv[1]);
	ft_putstr_fd("Sending to PID: ", 1);
	ft_putstr_fd(argv[1], 1);
	ft_putstr_fd("\nMessage: ", 1);
	ft_putstr_fd(argv[2], 1);
	signal(SIGUSR1, receive_handler);
	signal(SIGUSR2, receive_handler);
	if(!stringToBinary(server_pid, argv[2]))
		return (3);
	return (0);
}

static int	sendsig(int server_pid, char ch)
{
	int j;

	j = 7;
	while (j >= 0)
	{
		if (ch & (1 << j--))
		{
			if (kill(server_pid, SIGUSR1) == -1)
				return (0);
		}
		else
			if (kill(server_pid, SIGUSR2) == -1)
				return (0);
		pause();
		usleep(10);
	}
	return (1);
}

int	stringToBinary(int server_pid, char *s)
{
	int		i;
	int		len;
	char	ch;

	i = 0;
	if (s == NULL)
		return (0);
	len = strlen(s);
	while (i <= len)
	{
		ch = s[i++];
		if (!sendsig(server_pid, ch))
			return (0);
	}
	return (1);
}
