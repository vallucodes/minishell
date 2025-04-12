#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_env t_env;
typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;


# define FD_IN  0
# define FD_OUT 1
# define REDIR_IN  0
# define REDIR_OUT 1

typedef struct s_execution
{
	char 	**cmd_args;   // Command and its arguments
	int		redir_fd[2];        // temp_fd[FD_IN] = input, temp_fd[FD_OUT] = output
	int		temp_fd[2];   // Temporary fds (e.g., for saving stdin/stdout)
	int		prev_fd;
	int		pipefd[2];
	int		has_next_pipe;

}				t_execution;

void	traverse(t_ast *ast);
int		execute_builtin(t_minishell *mshell, char **cmd_args);
void	execute_ast(t_minishell *mshell, t_ast *ast);
int		safe_open_redirect(const char *filepath, int flags, int mode);
char	**get_command_argv(t_minishell *mshell, t_ast *ast);




#endif

