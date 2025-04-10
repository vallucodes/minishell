#include <signal.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

// Signal handler for SIGINT
void sigint_handler(int signal)
{
	printf("\nIntercepted SIGINT!\n");
}

void init_signal_action(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
}

void ignore_signal_action(struct sigaction *sa)
{
	sa->sa_handler = SIG_IGN;
	sigaction(SIGINT, sa, NULL);
}

void restart_signal_action(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler;
	sigaction(SIGINT, sa, NULL);
}

int main(void)
{
	struct sigaction sa;
	init_signal_action(&sa);
	// Change SIGINT's associated action
	ignore_signal_action(&sa);

	printf("Parsing...\n");
	sleep(5);
	printf("Parsing done. Now SIGINT can be handled.\n");

	restart_signal_action(&sa);
	while(1)
		continue ;
	return (0);
}
