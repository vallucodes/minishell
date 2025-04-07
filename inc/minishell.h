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
# include "ast.h"
# include "heredoc.h"
# include "environment.h"
# include "memory_arena.h"
# include "builtin.h"

# define PROMPT "\001\e[93m\002🦒 >>>\001\e[0m\e[95m\002 Giraffeshell>$ \001\e[0m\002"

//error prompts
# define BALANCE "quotes or brackets unbalanced"
# define REDIRECT "redirections invalid"
# define TOKEN_ERROR "syntax error near unexpected token"
# define PIPE_ERROR " `|'"
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

//functions
void	extract_token(t_minishell *mshell, t_input *input);
void	init_lexer(t_input *new_input, char *input_str);
int		input_validation(char *input);
int		tokens_validation(t_token *tokens);
void	retokenize_words(t_token *tokens);
void	concatinate_adjacecnt_quotes(char *str);
int		init_minishell(t_minishell *mshell, char **envp);


//tokenizer utils
int		is_separator(char c);
int		is_quote(char c);
int		is_operator(char c);
int		is_word(t_input *input, int i);
int		inquotes(char c, t_quotes_helper *quotes);
void	append_char(char *str, char **new, int i);

//global utils
int		any_redirect(t_token *current);
void	print_error(char *msg, char *token);
void	init_quotes(t_quotes_helper *quotes);
void	replace_content_of_token(t_token *current, char *new_str);

//heredoc
void	handle_heredoc(t_arena **arena, char **env, t_token *tokens);
char	*create_tmp_file(t_arena **arena, int *fd);
void	save_to_file(char **env, char *input, int fd, t_expand expand);
int		is_valid_char_expansion(char c);

//ast
t_ast	*build_ast_binary_tree(t_arena **arena, t_token *tokens);
void	build_branch(t_arena **arena, t_ast **ast, t_token *tokens, t_branch branch);
void	add_node(t_ast **ast, t_ast *new_node, t_order order);
t_ast	*init_node(t_arena **arena, char **cmd, char *file, t_token_type type);

//ast utils
int		count_amount_cmd(t_token *tokens);
size_t	get_amount_of_pipes(t_token *tokens);
int		is_any_redirect(t_token_type type);
int		last_is_pipe(t_ast **ast);
t_token	*skip_to_next_pipe(t_token *tokens);

//memory-arena
t_arena	arena_create();
void	*arena_alloc(t_arena *a, size_t size, size_t alignment);
void	arena_destroy(t_arena **a);
void	init_arena(t_arena **arena);

//remove quotes
void	expand_remove_quotes(char **env, t_token *tokens);

//developlment functions
void print_tokens(t_token *tokens);
char *get_token_type_name(t_token_type token_type);
void print_cmd(char **cmd);
void print_node(t_ast *node);
void print_left_side(t_ast *ast);
void print_whole_tree(t_ast *ast);

#endif
