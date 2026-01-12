/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:24:17 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/12 08:17:46 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minitalk.h"

static void	handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char	chr = 0;
	static int				bit = 0;

	(void)context;
	if (signo == SIGUSR1)
		chr |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_putchar_fd(chr, 1);
		if (chr == '\0')
			ft_putchar_fd('\n', 1);
		chr = 0;
		bit = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Use PID below w/ client to send message:\nServer PID: ", 1);
	ft_putnbr_fd((int)getpid(), 1);
	ft_putchar_fd('\n', 1);
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
