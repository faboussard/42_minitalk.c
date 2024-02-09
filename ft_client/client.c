#include "client.h"

void	send_bit(const char *message, pid_t pid, size_t message_len)
{
	size_t 		shift;
	size_t 		size_char_system;
	size_t	i;

	size_char_system = sizeof(char);
	i = 0;
	while (i <= message_len)
	{
		shift = 0;
		while (shift < size_char_system)
		{
			if ((message[i] >> shift) & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			shift++;
			usleep(1000);
		}
		i++;
	}
}

int main(int ac, char **av)
//int main(int ac, char **av)
{
	ac = 3;
	pid_t		pid;
	size_t 	message_len;
	char	*message;

	pid = ft_atoi(av[1]);
	message = av[2];
	message_len = ft_strlen(message);
	send_bit(message, pid, message_len);
}

