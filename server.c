#include "server_client.h"

char    *message = NULL;

void init_server()
{
	ft_printf("Welcome to Fafa's server\n");
	ft_printf("This server's ID is %d\n", getpid());
	ft_printf("Server is ready to listen\n");
}

static void fill_message(char *received, int *i)
{
    if (message == NULL)
    {
        message = malloc(sizeof(char) * 8);
        if (message == NULL)
            exit(EXIT_FAILURE);
    }
    message[(*i)++] = *received;
    message = ft_realloc(message, *i);
    if (message == NULL)
        exit(EXIT_FAILURE);
    if (*received == '\0')
    {
        ft_printf("Message received : %s\n", message);
        *i = 0;
        free(message);
        message = NULL;
    }
}

static void sigusr_handler(int signum)
{
	static char received = 0;
	static int  count = 0;
    static int  i = 0;

	if (signum == SIGUSR1 || signum == SIGUSR2)
	{
		count++;
		if (signum == SIGUSR1)
        {
            received <<= 1;
            received |= 0x01;
        }
		else
            received <<= 1;
		if (count == 8)
		{
		    fill_message(&received, &i);
            received = 0;
            count = 0;
		}
	}
}

void receive_signals()
{
	sa_usr.sa_handler = sigusr_handler;
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