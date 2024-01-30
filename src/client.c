/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:21:23 by ael-mank          #+#    #+#             */
/*   Updated: 2024/01/30 19:23:32 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int			g_received_bit;

static void	send_bit(int bit, pid_t pid)
{
	g_received_bit = 0;
	if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		if (kill(pid, SIGUSR1) == -1)
			exit(EXIT_FAILURE);
	}
	while (!g_received_bit)
	{
	}
}

static void	send_char(int c, int sent_bits, pid_t pid)
{
	sent_bits++;
	if (sent_bits < 8)
		send_char(c / 2, sent_bits, pid);
	if (c % 2 == 1)
		send_bit(1, pid);
	else
		send_bit(0, pid);
}

static void	handle_acknowledgment(int signum)
{
	(void)signum;
	g_received_bit = 1;
}

int	main(int argc, char **argv)
{
	signal(SIGUSR1, handle_acknowledgment);
	if (argc != 3 && ft_atoi(argv[1]) <= 0)
		return (EXIT_FAILURE);
	while (*argv[2])
	{
		send_char((unsigned char)*argv[2], 0, ft_atoi(argv[1]));
		argv[2]++;
	}
	send_char((unsigned char)0, 0, ft_atoi(argv[1]));
	ft_printf("Successfully sent message to PID %d\n", ft_atoi(argv[1]));
	return (EXIT_SUCCESS);
}
