/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:22:31 by faboussa          #+#    #+#             */
/*   Updated: 2024/02/15 12:22:42 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"
#include "server_client.h"

void	send_bit(const char *message, pid_t pid, size_t message_len)
{
	int		shift;
	size_t	i;

	i = 0;
	while (i <= message_len)
	{
		shift = 7;
		while (shift >= 0)
		{
			if ((message[i] >> shift) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(300);
			shift--;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int		pid;
	size_t	message_len;
	char	*message;

	if (ac != 3)
	{
		ft_printf("please enter your server pid and only ONE g_message");
		return (-1);
	}
	else
	{
		pid = ft_atoi(av[1]);
		if (pid <= 0)
			exit(EXIT_FAILURE);
		message = av[2];
		message_len = ft_strlen(message);
		send_bit(message, pid, message_len);
		exit(EXIT_SUCCESS);
	}
}
