#include "../../inc/minishell.h"
#include <sys/wait.h>

typedef struct s_exec_fd
{
	char 	**cmd_args; // cmds and arguments
	int		input_fd; //fd to read input from
	int		output_fd; //fd to write output to
}				t_exec_fd;

t_exec_fd
