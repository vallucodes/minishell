#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_env t_env;
typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;

// typedef struct s_exec_fd
// {
// 	char 	**cmd_args; // cmds and arguments
// 	int		input_fd; //fd to read input from
// 	int		output_fd; //fd to write output to
// 	int		temp_fd[2];
// }				t_exec_fd;

void	traverse(t_ast *ast);

#endif

// int fd[2];
// t_exec_fd dude;

// pipe(&dude.input_fd)
