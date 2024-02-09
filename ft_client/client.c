#include "client.h"

void send_bit(const char *message, pid_t pid, size_t message_len)
{
	int shift;
	size_t i;

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
			shift--;
			usleep(10000);
		}
		i++;
	}
}

int main(int ac, char **av)
{
	pid_t pid;
	size_t message_len;
	char *message;

	if (ac != 3)
	{
		ft_printf("please enter your server pid and only ONE message");
		return (-1);
	}
	else
	{
		pid = ft_atoi(av[1]);
		if (pid <= 0)
			EXIT_FAILURE;
		message = av[2];
		message_len = ft_strlen(message);
		send_bit(message, pid, message_len);
		EXIT_SUCCESS;
	}
}