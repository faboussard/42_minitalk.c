#include "server_client.h"
#include "libft/inc/libft.h"

char    *g_message = NULL;

void init_server()
{
	ft_printf("Welcome to Fafa's server\n");
	ft_printf("This server's ID is %d\n", getpid());
	ft_printf("Server is ready to listen\n");
}

static void fill_message(char *received, int *i)
{
    if (g_message == NULL)
    {
        g_message = malloc(sizeof(char) * 8);
        if (g_message == NULL)
            exit(EXIT_FAILURE);
    }
    g_message[(*i)++] = *received;
    g_message = ft_realloc(g_message, *i);
    if (g_message == NULL)
        exit(EXIT_FAILURE);
    if (*received == '\0')
    {
        ft_printf("Message received : %s\n", g_message);
        *i = 0;
        free(g_message);
        g_message = NULL;
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