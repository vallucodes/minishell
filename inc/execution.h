#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_env t_env;
typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;

# define FD_IN  0
# define FD_OUT 1

typedef struct s_exec
{
	int pipefd[2];    // current pipe fds
	int prev_fd;      // saved read-end from previous pipe
	pid_t pid;        // current child pid
	pid_t last_pid; // last pid
	int status;       // last status
	int has_pipe;
	int command_count;
}	t_exec;


//redirection
int	handle_redirection(t_ast *ast);
int	safe_dup2(int fd, int target_fd);
int	open_redir_file(const char *file, int flags, int *fd, t_ast *ast);

//setup
int		setup_pipe(t_exec *exec);
int		setup_fork(t_exec *exec);
void	setup_child_pipe_fds(t_minishell *mshell, t_exec *exec);
void	setup_parent_pipe_fds(t_minishell *mshell, t_exec *exec);


//execute builtins
t_ast	*get_cmd_node(t_ast *ast);
int		is_builtin(t_ast *ast);
int 	execute_builtin(t_minishell *mshell, t_ast *ast);
int		execute_builtin_alone(t_minishell *mshell, t_ast *ast);


//execute external
void	handle_child_process(t_minishell *mshell, t_ast *ast, t_exec *exec);

//get path
char	*get_command_path(t_minishell *mshell, t_ast *ast);

//execute controller
void execute_ast_v1(t_minishell *mshell, t_ast *ast);

//wait
int wait_for_children(t_exec *exec);

//delete
void close_origin_fds(t_minishell *mshell);


#endif

