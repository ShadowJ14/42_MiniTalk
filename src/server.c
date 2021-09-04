/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:55:52 by lprates           #+#    #+#             */
/*   Updated: 2021/09/04 04:30:46 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minitalk.h"

t_data	g_data;

int	main(void)
{
	struct sigaction	sig;
	sigset_t			ss;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	g_data.bits = 0;
	g_data.counter = 0;
	if (sigemptyset(&ss) == -1)
		return (1);
	sigaddset(&ss, SIGINT);
	sigaddset(&ss, SIGQUIT);
	sig.sa_handler = 0;
	sig.sa_sigaction = ft_sigreceived;
	sig.sa_flags = SA_SIGINFO;
	sig.sa_mask = ss;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
	return (0);
}

void	ft_sigreceived(int sig, siginfo_t *info, void *ucontext)
{
	static char	bits = 0;
	static int	counter = 0;

	(void)ucontext;
	if (sig == SIGUSR1)
		bits |= 0b00000001;
	if (counter >= 7)
	{
		ft_printchar(bits);
		bits = 0;
		counter = 0;
	}
	else
	{
		bits = bits << 1;
		counter++;
	}
	usleep(10);
	kill(info->si_pid, SIGUSR1);
}

void	ft_printchar(char bits)
{
	ft_putchar_fd(bits, 1);
	if (!bits)
		ft_putchar_fd('\n', 1);
}
