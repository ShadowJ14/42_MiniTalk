/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lprates <lprates@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:55:48 by lprates           #+#    #+#             */
/*   Updated: 2021/08/15 00:43:10 by lprates          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include "libft.h"

typedef struct s_data
{
	unsigned char	bits;
	unsigned char	counter;
	int				client_pid;
}				t_data;

void	ft_signactyes(int sig, siginfo_t *info, void *ucontext);
void	ft_signactno(int sig, siginfo_t *info, void *ucontext);
void	ft_printchar(void);

#endif