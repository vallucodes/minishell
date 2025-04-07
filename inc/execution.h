#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_env t_env;
typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;


#define FD_IN  0
#define FD_OUT 1

typedef struct s_execution
{
	char 	**cmd_args;   // Command and its arguments
	int		fd[2];        // fd[FD_IN] = input, fd[FD_OUT] = output
	int		temp_fd[2];   // Temporary fds (e.g., for saving stdin/stdout)
}				t_execution;


void	traverse(t_ast *ast);
int		execute_builtin(t_minishell *mshell, t_ast *ast);
void	execute_ast(t_minishell *mshell, t_ast *ast);
int		safe_open_redirect(const char *filepath, int flags, int mode);


#endif

// int fd[2];
// t_exec_fd dude;

// pipe(&dude.input_fd)
