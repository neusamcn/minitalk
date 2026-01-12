/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncruz-ne <ncruz-ne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 16:24:20 by ncruz-ne          #+#    #+#             */
/*   Updated: 2026/01/12 09:05:31 by ncruz-ne         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minitalk.h"

volatile sig_atomic_t	g_ack = 0;

static void	send_msg(unsigned char chr, __pid_t server_pid)
{
	unsigned int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_ack = 0;
		if (chr & (1 << bit))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		bit++;
		while (!g_ack)
			usleep(10);
	}
}
static void	handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
}

static void	init_sig(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
}

static long	ft_atol(const char *nptr)
{
	int		i;
	long	sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (ft_isdigit(nptr[i]) != 0)
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	if ((nb > INT_MAX && sign == -1) || (nb > INT_MAX && sign == 1))
	{
		ft_putstr_fd("****ERROR****\nInvalid PID (over integer range)\n", 1);
		ft_putstr_fd("Try sending message again.\n", 1);
		exit(EXIT_FAILURE);
	}
	return (nb * sign);
}

int	main(int ac, char **av)
{
	__pid_t	server_pid;
	int		i;

	if (ac == 3)
	{
		server_pid = ft_atol(av[1]);
		if (server_pid < 1 || kill(server_pid, 0) == -1)
		{
			ft_putstr_fd("****ERROR****\nInvalid server PID.\n\n", 1);
			ft_putstr_fd("Try sending message again.\n", 1);
			return (EXIT_FAILURE);
		}
		init_sig();
		i = 0;
		while (av[2][i])
			send_msg(av[2][i++], server_pid);
		send_msg('\0', server_pid);
		return (EXIT_SUCCESS);
	}
	ft_putstr_fd("****ERROR****\nIncorrect use of arguments\n\n", 1);
	ft_putstr_fd("How to use this program:\n", 1);
	ft_putstr_fd("./client server_PID \"your_message\"\n", 1);
	return (EXIT_FAILURE);
}
