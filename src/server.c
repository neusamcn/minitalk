/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:24:17 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/12 10:58:58 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minitalk.h"

static void	handler(int signo, siginfo_t *info, void *context)
{
	static unsigned char	chr = 0;
	static int				bit = 0;

	(void)context;
	if (signo == SIGUSR1)
		chr = chr | (1 << bit);
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

static void	init_sig_server(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Use PID below w/ client to send message:\nServer PID: ", 1);
	ft_putnbr_fd((int)getpid(), 1);
	ft_putstr_fd("\n\nServer is listening...\n", 1);
	ft_putstr_fd("Enter 'kill server_PID' from client to terminate\n", 1);
	init_sig_server();
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
