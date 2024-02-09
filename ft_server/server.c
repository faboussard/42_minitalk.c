#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void init_server()
{
	ft_printf("Welcome to Fafa's server\n");
	ft_printf("This server's ID is %d\n", getpid());
	ft_printf("Server is ready to listen\n");
}

static void sigusr_handler(int signum)
{
	static char received = 0;
	char *message;
	int count;
//	int i =0;

	count = 0;
	message = malloc(sizeof(char));
	printf("%lu", sizeof(message));
	if (message == NULL)
		return;
	if (signum == SIGUSR1)
	{
		write(1, "ok1", 3);
		count++;
		received |= 1;
	}
	else if (signum == SIGUSR2)
	{
		write(1, "ok2", 3);
		count++;
		received |= 0;
	}
//	if (count == 8)
//	{
//		message[i] = received;
//		received = 0;
//		message = ft_realloc(message, sizeof(char));
//		if (message == NULL)
//			return;
//		count = 0;
//		i++;
//	}
}

void receive_signals()
{
	struct sigaction sa_usr;

	sa_usr.sa_handler = sigusr_handler;
	sigemptyset(&sa_usr.sa_mask);
	sa_usr.sa_flags = 0;
	sigaction(SIGUSR1, &sa_usr, NULL);
	sigaction(SIGUSR2, &sa_usr, NULL);
}

int main()
{
	char *message;
	message = malloc(sizeof(char));
	printf("%lu", sizeof(message));
	init_server();
	receive_signals();
	while (1)
		pause();

	//si message termine, print tout
	return 0;
}