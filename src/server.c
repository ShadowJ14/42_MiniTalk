/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:55:52 by lprates           #+#    #+#             */
/*   Updated: 2021/08/21 17:36:35 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "minitalk.h"

t_data	g_data;

int	main(void)
{
	struct sigaction	sigactyes;
	struct sigaction	sigactno;

	ft_putstr_fd("Server PID: ", 1);
	ft_putstr_fd(ft_itoa(getpid()), 1);
	ft_putstr_fd("\n", 1);
	g_data.bits = 0b00000000;
	g_data.counter = 0;
	sigactyes.sa_sigaction = &ft_signactyes;
	sigactno.sa_sigaction = &ft_signactno;
	sigactyes.sa_flags = SA_SIGINFO;
	sigactno.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigactyes, NULL);
	sigaction(SIGUSR2, &sigactno, NULL);
	while (1)
		pause();
	return (0);
}

void	ft_signactyes(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)sig;
	g_data.bits |= 0b00000001;
	if (!g_data.client_pid)
		g_data.client_pid = info->si_pid;
	kill(g_data.client_pid, SIGUSR2);
	if (g_data.counter == 7)
		ft_printchar();
	else
	{
		g_data.bits = g_data.bits << 1;
		g_data.counter++;
	}
}

void	ft_signactno(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)sig;
	if (!g_data.client_pid)
		g_data.client_pid = info->si_pid;
	kill(g_data.client_pid, SIGUSR2);
	if (g_data.counter == 7)
		ft_printchar();
	else
	{
		g_data.bits = g_data.bits << 1;
		g_data.counter++;
	}
}

void	ft_printchar(void)
{
	ft_putchar_fd(g_data.bits, 1);
	//usleep(10);
	if (!g_data.bits)
	{
		ft_putchar_fd('\n', 1);
		kill(g_data.client_pid, SIGUSR1);
		g_data.client_pid = 0;
	}
	g_data.counter = 0;
	g_data.bits = 0b00000000;
}
