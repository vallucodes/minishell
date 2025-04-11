#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>			//close
# include <stdlib.h> 			//free
# include <stdio.h>				//printf
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline
# include <fcntl.h>				//open
# include <stdalign.h>			//alignof
# include <signal.h>			//signals
# include "../lib/libft/inc/libft.h"
# include "signals.h"
# include "lexing.h"
# include "memory_arena.h"
# include "ast.h"
# include "heredoc.h"
# include "environment.h"
# include "builtin.h"

# define PROMPT "\001\e[93m\002🦒 >>>\001\e[0m\e[95m\002 Giraffeshell>$ \001\e[0m\002"

//error prompts
# define BALANCE "quotes or brackets unbalanced"
# define REDIRECT "redirections invalid"
# define TOKEN_ERROR "syntax error near unexpected token"
# define UNREACHABLE "This is unreachable code, something is wrong with error handling\n"
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
	struct sigaction	*sa;
	t_arena				*arena;
	t_env				*envp; // env struct
	int					exitcode; //exitcode assignment after exe
	//later add execution, exit code when we are there
}				t_minishell;

//error handling
void	print_error(char *msg, char *token, t_token_type type);

//global utils
void	append_char(char *str, char **new, int i);
int		is_any_redirect(t_token *current);
void	init_quotes(t_quotes_helper *quotes);
void	replace_content_of_token(t_token *current, char *new_str);

//main functions
int		init_minishell(struct sigaction	*sa, t_minishell *mshell, char **envp);
int		input_validation(char *input);

//quote handler
void	expand_remove_quotes(char **env, int return_value, t_token *tokens);

//quote utils
int		is_valid_expandable(t_quotes_helper quotes, char *input_str);
int		there_is_quote_state_change(t_quotes_helper quotes);
int		is_any_word(t_token_type type);
int		expandable_exists(int len, char **env, int i, char *str);
int		is_exitcode_expansion(t_quotes_helper quotes, char *input_str);
int		is_pid_expansion(t_quotes_helper quotes, char *input_str);
void	replace_content_of_token(t_token *current, char *new_str);

//expansion
size_t	expand_pid(int fd, char **new_str);
size_t	expand_content(char **env, char *str, int fd, char **new_str);
size_t	expand_exitcode_value(int exitcode, int fd, char **new_str);

//developlment functions
void print_tokens(t_token *tokens);
char *get_token_type_name(t_token_type token_type);
void print_cmd(char **cmd);
void print_node(t_ast *node);
void print_left_side(t_ast *ast);
void print_whole_tree(t_ast *ast);

#endif
