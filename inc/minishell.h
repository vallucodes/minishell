#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>			//close
# include <stdlib.h> 			//free
# include <stdio.h>				//printf
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline
# include <fcntl.h>				//open
# include <stdalign.h>			//alignof
# include "../lib/libft/inc/libft.h"
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
	t_arena	*arena;
	t_env	*envp; // env struct
	int		exitcode; //exitcode assignment after exe
	//later add execution, exit code when we are there
}				t_minishell;

//error handling
void	print_error(char *msg, char *token, t_token_type type);

//global utils
void	append_char(char *str, char **new, int i);
int		is_any_redirect(t_token *current);
void	init_quotes(t_quotes_helper *quotes);
void	replace_content_of_token(t_token *current, char *new_str);

//functions
int		input_validation(char *input);
int		tokens_validation(t_token *tokens);
int		init_minishell(t_minishell *mshell, char **envp);

//tokenizer
void	init_lexer(t_input *new_input, char *input_str);
int		tokenizer(t_minishell *mshell, t_input *input, char *input_str);
void	retokenize_words(t_token *tokens);

//tokenizer utils
int		is_separator(char c);
int		is_quote(char c);
int		is_operator(char c);
int		is_valid_char(t_quotes_helper *quotes, t_input *input);
void	update_quote_state(char c, t_quotes_helper *quotes);

//heredoc
void	handle_heredoc(t_arena **arena, char **env, t_token *tokens);
char	*create_tmp_file(t_arena **arena, int *fd);
void	save_to_file(char **env, char *input, int fd, t_expand expand);
int		is_valid_char_expansion(char c);

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
