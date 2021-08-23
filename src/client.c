/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:56:29 by lprates           #+#    #+#             */
/*   Updated: 2021/08/21 17:36:34 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	check_pid(const char *str)
{
	while (*str && ft_isdigit(*str))
		str++;
	return (!*str);
}

void	ft_sigtrig(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)sig;
	(void)info;
	return ;
}

int	main(int argc, char *argv[])
{
	int		server_pid;
	struct sigaction	sigactend;
	struct sigaction	sigtrig;

	if (argc != 3)
		return (1);
	if (!check_pid(argv[1]))
		return (2);
	server_pid = ft_atoi(argv[1]);
	sigactend.sa_sigaction = &ft_signactend;
	sigactend.sa_flags = SA_SIGINFO;
	sigtrig.sa_sigaction = &ft_sigtrig;
	sigtrig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigactend, NULL);
	sigaction(SIGUSR2, &sigtrig, NULL);
	ft_putstr_fd("Sending to PID: ", 1);
	ft_putstr_fd(argv[1], 1);
	ft_putstr_fd("\nMessage: ", 1);
	ft_putstr_fd(argv[2], 1);
	if(!stringToBinary(server_pid, argv[2]))
		return (3);
	sleep(5);
}

int	stringToBinary(int server_pid, char *s)
{
	int		i;
	int		j;
	int		len;
	char	ch;

	i = 0;
	j = 7;
	if (s == NULL)
		return (0);
	len = strlen(s);
	while (i <= len)
	{
		ch = s[i++];
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
			// usleep(50);
		}
		j = 7;
	}
	return (1);
}

void	ft_signactend(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)sig;
	(void)info;
	ft_putstr_fd("\nMessage received!\n", 1);
	exit(0);
}