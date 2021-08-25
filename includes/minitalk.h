/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:55:48 by lprates           #+#    #+#             */
/*   Updated: 2021/08/21 16:23:45 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "libft.h"

typedef struct s_data
{
	unsigned char	bits;
	unsigned int	counter;
}				t_data;

void	ft_sigreceived(int sig, siginfo_t *info, void *ucontext);
void	ft_printchar(char bits);
int		stringToBinary(int server_pid, char *s);

#endif