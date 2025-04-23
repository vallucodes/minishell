#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>			//close
# include <stdlib.h> 			//free
# include <stdio.h>				//printf
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline
# include <fcntl.h>				//open
# include <stdalign.h>			//alignof
# include <errno.h>
# include <signal.h>			//signals
# include <limits.h>			//FILE_MAX
# include <sys/wait.h>
# include <sys/stat.h>
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

# define PROMPT "\001\e[93m\002🦒 >>>\001\e[0m\e[95m\002 Giraffeshell>$ \001\e[0m\002"

//error prompts
# define AC "Error: invalid number of arguments!\n"
# define BALANCE "Error: quotes or brackets unbalanced\n"
# define REDIR "Error: redirections invalid\n"
# define TOKEN_ERROR "syntax error near unexpected token"
# define UNREACHABLE "This is unreachable code, something is wrong with error handling\n"
# define TMP_FILES "Too many heredoc redirections\n"
# define PIPE_ERROR " `|'"
# define INFILE_ERROR " `<'"
# define OUTFILE_ERROR " `>'"
# define APPENDFILE_ERROR " `>>'"
# define HEREDOC_ERROR " `<<'"
# define NEWLINE_ERROR " `newline'"
# define MALLOC "malloc fail"

typedef enum e_exit
{
	SUCCESS,
	FAIL,
}	t_exit;

typedef struct s_minishell
{
	t_arena		*arena;
	t_env		*envp;
	t_ast		*ast;
	int			exitcode;
	char		**path;
	char 		*input_str;
	int			origin_stdin;
	int			origin_stdout;
	int			in_child;
	size_t		rl_count;
	size_t		rl_count_heredoc;
}				t_minishell ;

//main functions
int		input_validation(char *input);
int		init_minishell(t_minishell *mshell, char **envp, t_ast **ast);
void	init_quotes(t_quotes_helper *quotes);

//errors, exits and cleanups
void	delete_minishell(t_minishell *mshell);
void	exit_and_cleanup(t_minishell *mshell);
void	exit_error(t_minishell *mshell, char *msg);
void	exit_cleanup_error(t_minishell *mshell, char *msg);
void	print_error(char *msg, char *token, t_token_type type);

//global utils
void	append_char(t_minishell *mshell, char *src, char **dst, size_t i);
int		is_any_redirect(t_token *current);
void	replace_content_of_token(t_token *current, char *new_str);
bool	there_is_quote_state_change(t_quotes_helper quotes);

//quote handler
void	expand_remove_quotes(t_minishell *mshell, t_input *input);
void	init_vars(t_minishell *mshell, t_vars *vars, t_token *current);

//quote utils
bool	is_valid_expandable(t_quotes_helper quotes, char *input_str);
bool	is_any_word(t_token_type type);
bool	expandable_exists(int len, char **env, size_t i, char *str);
bool	is_exitcode_expansion(t_quotes_helper quotes, char *input_str);
bool	is_pid_expansion(t_quotes_helper quotes, char *input_str);
bool	is_exp_is_empty_is_bare_is_cmd_or_arg(t_vars vars, t_token *curr);

void	update_vars_quote(t_vars *vars, size_t *i);
void	update_vars_append(t_minishell *mshell, t_vars *vars, size_t *i);

//expansion
size_t	expand_pid(t_minishell *mshell, int fd, char **new_str);
size_t	expand_content(t_minishell *mshell, char *str, int fd, char **new_str);
size_t	expand_exitcode_value(t_minishell *mshell, int fd, char **new_str);
void	write_or_add_to_str(t_minishell *mshell, int fd, char **new_str, char *str_pid);
size_t		skip_to_start_of_expandable(char *env_row);
size_t	get_len_explandeble(char *str);

//developlment functions
void print_tokens(t_token *tokens);
char *get_token_type_name(t_token_type token_type);
void print_cmd(char **cmd);
void print_node(t_ast *node);
void print_left_side(t_ast *ast);
void print_whole_tree(t_ast *ast);

#endif
