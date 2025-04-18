#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_signal;

void	sigint_handler_main(int signal);
void	sigint_handler_heredoc(int signal);
void	sigint_handler_parent(int signal);

// int		init_signals(struct sigaction *sa);
int		signal_action_ignore(void);
int		signal_action_main(void);
int		signal_action_heredoc(void);
int		signal_action_parent(void);
int		signal_action_default(void);

#endif
