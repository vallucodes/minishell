#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_signal;

void	sigint_handler_main(int signal);
void	sigint_handler_heredoc(int signal);
void	init_signals(struct sigaction *sa);
void	ignore_signal_action(struct sigaction *sa);
void	restart_signal_action_main(struct sigaction *sa);
void	restart_signal_action_heredoc(struct sigaction *sa);

#endif
