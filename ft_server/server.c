#include "server.h"
#include <stdio.h>

char *message = NULL;

void init_server()
{
	ft_printf("Welcome to Fafa's server\n");
	ft_printf("This server's ID is %d\n", getpid());
	ft_printf("Server is ready to listen\n");
}

static void sigusr_handler(int signum)
{
	static unsigned char received = 0;
	static int count = 0;
	static int i = 0;

	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		count++;
		if (signum == SIGUSR1)
		{
			received <<= 1;
			received |= 0x01;
		}
		else if(signum == SIGUSR2)
			received <<= 1;
		if (count == 8)
		{
			if (message == NULL)
			{
				message = malloc(sizeof(char) * 8);
				if (message == NULL)
					return;
			}
			message[i] = (char)received;
			i += 1;
			message = ft_realloc(message, i);
			if (message == NULL)
				return;
			if (received == '\0')
			{
				ft_printf("%s\n", message);
				i = 0;
			}
			received = 0;
			count = 0;
		}
	}
	else
		ft_printf("wrong signum");
}

void receive_signals()
{
	struct sigaction sa_usr;

	sa_usr.sa_handler = sigusr_handler;
	sigemptyset(&sa_usr.sa_mask);
	sa_usr.sa_flags = SA_SIGINFO | SA_RESTART;;
	sigaction(SIGUSR1, &sa_usr, NULL);
	sigaction(SIGUSR2, &sa_usr, NULL);
}

int main()
{
	init_server();
	receive_signals();
	while (1)
		pause();
}