#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_env t_env;
typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;


# define FD_IN  0
# define FD_OUT 1

typedef struct s_execution
{
	char 	**cmd_args;   // Command and its arguments
	int		redir_fd[2];        // temp_fd[FD_IN] = input, temp_fd[FD_OUT] = output
	int		prev_fd;
	int		pipefd[2];
	int		has_next_pipe;

}				t_execution;

int		handle_redirections(t_ast *node, t_execution *exec);
char	**get_command_argv(t_minishell *mshell, t_ast *ast);
int		execute_builtin(t_minishell *mshell, char **cmd_args);
void	execute_ast(t_minishell *mshell, t_ast *ast);




void setup_child_fds(int prev_fd, int *pipefd, int has_next_pipe, t_execution *exec);



#endif

