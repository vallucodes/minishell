#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h> 			//free
# include <stdio.h>				//printf
# include <readline/readline.h>	//readline
# include <readline/history.h>	//readline

# define PROMPT "\001\e[93m\002>>> \001\e[0m\e[95m\002 Minishell>$ \001\e[0m\002"

#endif
