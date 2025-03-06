#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h> 			//free
# include <stdio.h>				//printf
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline

# define PROMPT "\001\e[93m\002🦒 >>>\001\e[0m\e[95m\002 Giraffeshell>$ \001\e[0m\002"


typedef enum e_types
{
	WORD,			// some word in double quotes "Something here"
	PIPE,			// |
	REDIRECT,		// < >
	APPEND,			// >>
	HERE_STRING,	// <<
	DOLLAR,			// $
}	t_types;

typedef struct s_input
{
	char			*token;
	t_types			token_type;
	struct s_input	*next;
}	t_input;


#endif
