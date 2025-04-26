/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:08:30 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/26 21:40:59 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_env		t_env;
typedef struct s_ast		t_ast;
typedef struct s_minishell	t_minishell;

# define FD_IN  0
# define FD_OUT 1

typedef struct s_exec
{
	int		pipefd[2];
	int		prev_fd;
	pid_t	pid;
	pid_t	last_pid;
	int		has_pipe;
	int		command_count;
}	t_exec;

int		handle_redirection(t_ast *ast);
int		safe_dup2(int fd, int target_fd);
int		open_redir_file(const char *file, int flags, int *fd, t_ast *ast);
int		setup_pipe(t_exec *exec);
int		setup_fork(t_exec *exec);
void	setup_child_pipe_fds(t_minishell *mshell, t_exec *exec);
void	setup_parent_pipe_fds(t_minishell *mshell, t_exec *exec);
t_ast	*get_cmd_node(t_ast *ast);
int		is_builtin(t_ast *ast);
int		execute_builtin(t_minishell *mshell, t_ast *ast);
int		execute_builtin_alone(t_minishell *mshell, t_ast *ast);
void	handle_child_process(t_minishell *mshell, t_ast *ast, t_exec *exec);
char	*get_command_path(t_minishell *mshell, t_ast *ast);
void	execute_ast(t_minishell *mshell, t_ast *ast);
int		wait_for_children(t_exec *exec);
void	close_origin_fds(t_minishell *mshell);

#endif
