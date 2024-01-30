/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mank <ael-mank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:21:25 by ael-mank          #+#    #+#             */
/*   Updated: 2024/01/30 20:20:51 by ael-mank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_character(unsigned char character, int *message_number,
				int *printed_message_number);

static void	receive_character(int bit, pid_t sender_pid);

static void	receive_character(int bit, pid_t sender_pid)
{
	static unsigned char	character;
	static int				received_bits;
	static pid_t			current_sender_pid;
	static int				message_number = 1;
	static int				printed_message_number = 0;

	if (sender_pid != current_sender_pid)
		current_sender_pid = sender_pid;
	character = character * 2 + bit;
	if (++received_bits == 8)
	{
		print_character(character, &message_number, &printed_message_number);
		character = 0;
		received_bits = 0;
	}
	kill(current_sender_pid, SIGUSR1);
}

static void	print_character(unsigned char character, int *message_number,
		int *printed_message_number)
{
	if (character == '\0')
	{
		write(1, "\n", 1);
		(*message_number)++;
		*printed_message_number = 0;
	}
	else
	{
		if (!*printed_message_number)
		{
			ft_printf("%s[%d] %s", BBLU, *message_number, CRESET);
			*printed_message_number = 1;
		}
		write(1, &character, 1);
	}
}

static void	handle_sigusr1(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	receive_character(0, info->si_pid);
}

static void	handle_sigusr2(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	receive_character(1, info->si_pid);
}

void print_header(void)
{
    ft_printf("\033[0;31m░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\033[0m\n");
	ft_printf("\033[0;31m░  ░░░░  ░░        ░░   ░░░  ░░        ░░        ░░░      ░░░  ░░░░░░░░  ░░░░  ░\033[0m\n");
    ft_printf("\033[0;31m▒   ▒▒   ▒▒▒▒▒  ▒▒▒▒▒    ▒▒  ▒▒▒▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒  ▒▒\033[0m\n");
    ft_printf("\033[0;31m▓        ▓▓▓▓▓  ▓▓▓▓▓  ▓  ▓  ▓▓▓▓▓  ▓▓▓▓▓▓▓▓  ▓▓▓▓▓  ▓▓▓▓  ▓▓  ▓▓▓▓▓▓▓▓     ▓▓▓▓\033[0m\n");
    ft_printf("\033[0;31m█  █  █  █████  █████  ██    █████  ████████  █████        ██  ████████  ███  ██\033[0m\n");
    ft_printf("\033[0;31m█  ████  ██        ██  ███   ██        █████  █████  ████  ██        ██  ████  █\033[0m\n");
	ft_printf("\033[0;31m████████████████████████████████████████████████████████████████████████████████\033[0m\n");
}

int	main(void)
{
	struct sigaction	sig_action1;
	struct sigaction	sig_action2;

	ft_bzero(&sig_action1, sizeof(struct sigaction));
	sig_action1.sa_flags = SA_SIGINFO;
	sig_action1.sa_sigaction = &handle_sigusr1;
	sigaction(SIGUSR1, &sig_action1, NULL);
	ft_bzero(&sig_action2, sizeof(struct sigaction));
	sig_action2.sa_flags = SA_SIGINFO;
	sig_action2.sa_sigaction = &handle_sigusr2;
	sigaction(SIGUSR2, &sig_action2, NULL);
	print_header();
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
	}
}
