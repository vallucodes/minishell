/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:13:49 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/27 13:14:20 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline
# include <fcntl.h>				//open, O_CREAT, O_WRONLY
# include <stdalign.h>			//alignof
# include <errno.h>				//errno
# include <signal.h>			//signals
# include <sys/wait.h>			//wait
# include <sys/stat.h>			//S_ISDIR
# include <stdbool.h>			//bool
# include "../lib/libft/inc/libft.h"
# include "signals.h"
# include "lexing.h"
# include "memory_arena.h"
# include "ast.h"
# include "heredoc.h"
# include "environment.h"
# include "builtin.h"
# include "execution.h"
# include "quotes_handler.h"
# include "expansion.h"
# include "error.h"

# define PROMPT "\001\e[93m\002🦒 >>>\001\e[0m\e[95m\002 \
Giraffeshell>$ \001\e[0m\002"

extern volatile sig_atomic_t	g_signal;

typedef enum e_exit
{
	SUCCESS,
	FAIL,
}	t_exit;

typedef struct s_minishell
{
	t_arena		*arena;
	t_env		*envp;
	int			exitcode;
	char		**path;
	char		*input_str;
	int			origin_stdin;
	int			origin_stdout;
	int			in_child;
	size_t		rl_count;
	size_t		rl_count_heredoc;
}				t_minishell;

//main functions
int		input_validation(t_minishell *mshell);
int		init_minishell(t_minishell *mshell, char **envp, t_ast **ast,
			char **av);
void	run_minishell(t_minishell *mshell, t_input *input, t_ast **ast);
void	init_quotes(t_quotes_helper *quotes);
void	increment_shlvl(t_env *env);

//global utils
void	append_char(t_minishell *mshell, char *src, char **dst, size_t i);
int		is_any_redirect(t_token *current);
void	replace_content_of_token(t_token *current, char *new_str);
bool	there_is_quote_state_change(t_quotes_helper quotes);

#endif
