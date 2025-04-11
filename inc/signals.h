#ifndef SIGNALS_H
# define SIGNALS_H

void	sigint_handler(int signal);
void	init_signals(struct sigaction *sa);
void	ignore_signal_action(struct sigaction *sa);
void	restart_signal_action(struct sigaction *sa);

#endif
