#include "server.h"

char received;

int listen()
{
	int count;

	received = 0;
	count = 0;
	if (SIGUSR1)
	{
		received |= 1;
		count += 1;
	}
	if (SIGUSR2)
	{
		received |= 0;
		count += 1;
	}
	return (count);
}

int main()
{
	int	 count;
	char *message;

	count = 0;
	ft_printf("this server's id is %d\n", getpid());
	ft_printf("server is ready to listen");

	message = malloc(sizeof(char));
	ft_printf("%d", sizeof(message));
	if (message == NULL)
		return (0);
	while (count <= 8)
	{
		count += listen();
		*message++ = received;
	}
	if (count > 8)
	{
		message = ft_realloc(message, sizeof(char));
		ft_printf("%d", sizeof(message));
	}
	count = 0;
}