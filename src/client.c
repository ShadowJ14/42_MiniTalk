/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:56:29 by lprates           #+#    #+#             */
/*   Updated: 2021/08/14 23:37:23 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char *argv[])
{
	char	*str;
	int		server_pid;

	if (argc != 3)
		return (1); // placeholder for error function
	str = argv[2];
	server_pid = ft_atoi(argv[1]);
	/*ft_putstr_fd(str, 1);
	ft_putstr_fd("\n", 1);*/
	ft_putstr_fd(argv[1], 1);
	stringToBinary(server_pid, str);
}

void	stringToBinary(int pid, char *s)
{
	int		i;
	int		j;
	int		len;
	char	ch;

	i = 0;
	j = 7;
	if (s == NULL)
		return ;
	len = strlen(s);
	while (i <= len)
	{
		ch = s[i++];
		while (j >= 0)
		{
			if (ch & (1 << j--))
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
		j = 7;
	}
	return ;
}
