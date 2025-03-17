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
# define BALANCE "quotes or brackets unbalanced"

typedef enum e_exit
{
	SUCCESS,
	FAIL,
}	t_exit;

//functions
void	print_error(char *msg);
void	extract_token(t_input *input);
void	init_lexer(t_input *new_input, char *input_str);
int		input_validation(char *input);

#endif
