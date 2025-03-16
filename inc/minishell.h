#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h> 			//free
# include <stdio.h>				//printf
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline
# include "../lib/libft/inc/libft.h"

# define PROMPT "\001\e[93m\002🦒 >>>\001\e[0m\e[95m\002 Giraffeshell>$ \001\e[0m\002"
# define BALANCE "quotes or brackets unbalanced"

typedef enum e_token_type
{
	WORD_DOUBLE,		// some word in double quotes "Something here"
	WORD_SINGLE,		// some word in single quotes 'Something here'
	PIPE,				// |
	REDIRECT_IN,		// <
	REDIRECT_OUT,		// >
	REDIRECT_APPEND,	// >>
	HERE_STRING,		// <<
	ENV_VAR,			// $
}	t_token_type;

typedef enum e_quotes
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quotes;

typedef struct s_token
{
	char			*value;
	int				len;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct	s_input
{
	char 	*full_str;	// The full user input
	int		index;		//track position while scanning
	int		len;		// len helps check if end of input is reached
	t_token	*tokens;
}				t_input;


//functions
void	extract_token(t_input *input);
void	init_lexer(t_input *new_input, char *input_str);


#endif
