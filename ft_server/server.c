#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t received = 0;

static void sigusr1_handler(int signum) {
	received |= 1;
}

static void sigusr2_handler(int signum) {
	received |= 0;
}

void init_sigaction() {
	struct sigaction sa_usr1, sa_usr2;

	sa_usr1.sa_handler = sigusr1_handler;
	sigemptyset(&sa_usr1.sa_mask);
	sa_usr1.sa_flags = 0;
	sigaction(SIGUSR1, &sa_usr1, NULL);

	sa_usr2.sa_handler = sigusr2_handler;
	sigemptyset(&sa_usr2.sa_mask);
	sa_usr2.sa_flags = 0;
	sigaction(SIGUSR2, &sa_usr2, NULL);
}

int main() {
	int count = 0;
	char *message;

	ft_printf("Welcome to Fafa's server\n");
	ft_printf("This server's ID is %d\n", getpid());
	ft_printf("Server is ready to listen\n");

	message = malloc(sizeof(char));
	if (message == NULL) {
		perror("malloc");
		return EXIT_FAILURE;
	}
	while (1)
	{
		init_sigaction();
		message[count] = (char)received;
		count++;

		if (count >= sizeof(char)) {
			message = realloc(message,  sizeof(char));
			if (message == NULL) {
				perror("realloc");
				return EXIT_FAILURE;
			}
		}
		ft_printf("Message reçu : %c\n", message[count - 1]);
		received = 0;
	}
	free(message);
	return 0;
}
