#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_signal;

typedef struct s_minishell t_minishell;

void	sigint_handler_main(int signal);
void	sigint_handler_heredoc(int signal);
void	sigint_handler_parent(int signal);

int		sig_action_ignore(t_minishell *mshell);
int		sig_action_main(t_minishell *mshell);
int		sig_action_heredoc(t_minishell *mshell);
int		sig_action_parent(t_minishell *mshell);
int		sig_action_default(t_minishell *mshell);

void	set_exitcode_signal(t_minishell *mshell);

#endif
