#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h> 			//free
# include <stdio.h>				//printf
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline
# include "../lib/libft/inc/libft.h"
# include "lexing.h"
# include "ast.h"

# define PROMPT "\001\e[93m\002🦒 >>>\001\e[0m\e[95m\002 Giraffeshell>$ \001\e[0m\002"

//error prompts
# define BALANCE "quotes or brackets unbalanced"
# define REDIRECT "redirections invalid"
# define TOKEN_ERROR "syntax error near unexpected token"
# define PIPE_ERROR " `|'"
# define NEWLINE_ERROR " `newline'"

typedef enum e_exit
{
	SUCCESS,
	FAIL,
}	t_exit;

//functions
void	print_error(char *msg, char *token);
void	extract_token(t_input *input);
void	init_lexer(t_input *new_input, char *input_str);
int		input_validation(char *input);
int		tokens_validation(t_token *tokens);

void print_tokens(t_token *tokens);

#endif
