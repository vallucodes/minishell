#include "../../inc/minishell.h"
#include <sys/wait.h>

/* DOCUMENTATION
1. Start at the root (topmost PIPE node)
2. Always run the command on .next_left. That can include redir or builtins
3. After executing .next_left, we:
		node = node->next_right;
		that means we teleport to the next PIPE node
4. Repeat until node == NULL - end of pipeline

EXAMPLE!
        PIPE 1
       /    \
   cat      PIPE 2
           /    \
      grep       wc

1. node = PIPE 1
   → node->next_left = cat
   → Run `cat`, setup stdout to pipe1[1]
   → Close pipe1[1] in parent
   → Move to: node = node->next_right → PIPE 2

2. node = PIPE 2
   → node->next_left = grep
   → Run `grep`, setup stdin = pipe1[0], stdout = pipe2[1]
   → Close pipe1[0], pipe2[1] in parent
   → Move to: node = node->next_right → wc

3. node = wc (this is just the last command in .next_left of the final pipe)
   → Run `wc`, setup stdin = pipe2[0], stdout = STDOUT_FILENO
   → Close pipe2[0] in parent
   → Done!
-------------------------------------------------------------------------------
*/


//check whether the command has a file redirection
// static t_execution init_execution(t_ast *branch)
// {
// 	t_execution exec;

// 	exec.cmd_args = NULL;
// 	exec.temp_fd[FD_IN] = STDIN_FILENO;
// 	exec.temp_fd[FD_OUT] = STDOUT_FILENO;

// 	while (branch)
// 	{
// 		if (branch->type == REDIRECT_IN || branch->type == HERE_STRING)
// 			exec.temp_fd[FD_IN] = safe_open_redirect(branch->file, O_RDONLY, 0);
// 		else if (branch->type == REDIRECT_OUT)
// 			exec.temp_fd[FD_OUT] = safe_open_redirect(branch->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		else if (branch->type == REDIRECT_APPEND)
// 			exec.temp_fd[FD_OUT] ft_d= safe_open_redirect(branch->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		else if (branch->type == COMMAND)
// 			exec.cmd_args = branch->cmd; // need to detect builtins here
// 		branch = branch->next_left;
// 	}
// 	return exec;
// }



static int	is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 ||
	ft_strcmp(cmd, "cd") == 0 ||
	ft_strcmp(cmd, "pwd") == 0 ||
	ft_strcmp(cmd, "export") == 0 ||
	ft_strcmp(cmd, "unset") == 0 ||
	ft_strcmp(cmd, "env") == 0 ||
	ft_strcmp(cmd, "exit") == 0
	);
}

//was here yesterday, now we have the
// =    at 0x49AF3EA: wait4 (wait4.c:30)
// ==144325==    by 0x406294: execute_ast (execution.c:240)
// ==144325==    by 0x4013DC: main (main.c:43)

//need allocate pids and wait for the last one.
// int	wait_for_children(t_minishell *mshell)
// {
// 	int		i;
// 	int		wstatus;
// 	int		exit_code;
// 	pid_t	pid;

// 	i = 0;
// 	exit_code = 0;
// 	while (i < mshell->command_count)
// 	{
// 		pid = waitpid(mshell->pids[i], &wstatus, 0);

// 		if (pid == mshell->pids[mshell->command_count - 1])
// 			exit_code = WEXITSTATUS(wstatus);
// 		i++;
// 	}
// 	return (exit_code);
// }


int	wait_for_children(t_minishell *mshell)
{
	int		i;
	int		wstatus;
	int		exit_code;

	i = 0;
	exit_code = 0;

	while (i < mshell->command_count)
	{
		if (mshell->last_pid == wait(&wstatus))
			exit_code = WEXITSTATUS(wstatus);
		i++;
	}
	printf("Child process%d\n", mshell->command_count);
	return (exit_code);
}

void execute_ast(t_minishell *mshell, t_ast *ast)
{
	t_ast *node;
	t_ast *cmd_node = NULL;
	int pipefd[2];
	pid_t	pid;
	t_execution exec;
	int has_next_pipe;
	int prev_fd = STDIN_FILENO;
	int status;
	char **external_cmd;

	node = ast;
	while (ast)
	{
		//You always run the command on the left side of the pipe node
		//after running all the left one, then you move right
		// exec = init_execution(node); //init for all redirection + command

		node = ast; // ast should stay as it is!
		//exec.cmd_args = NULL;
		exec.temp_fd[FD_IN] = STDIN_FILENO;
		exec.temp_fd[FD_OUT] = STDOUT_FILENO;

		has_next_pipe = (ast->next_right != NULL); //PIPE ALWAYS ON RIGHT, if not null then there is next
		if (has_next_pipe && pipe(pipefd) < 0)
			{
				perror("pipe");
				return;
			}

		while (node)
		{
			if (node->type == REDIRECT_IN || node->type == HERE_DOCUMENT)
				exec.temp_fd[FD_IN] = safe_open_redirect(node->file, O_RDONLY, 0);
			else if (node->type == REDIRECT_OUT)
				exec.temp_fd[FD_OUT] = safe_open_redirect(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (node->type == REDIRECT_APPEND)
				exec.temp_fd[FD_OUT] = safe_open_redirect(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else if (node->type == COMMAND)
			{
				exec.cmd_args = node->cmd;
				cmd_node = node;
				printf("DEBUG: Found COMMAND node: %s\n", node->cmd[0]);
			}
			node = node->next_left;
		}

		//check if cmd args is null

		if(!exec.cmd_args || !exec.cmd_args[0])
		{
			ast = ast->next_right;
			continue;
		}

		// must handle builtin in parent if it's not in a pipe
		//standalone builtin
		if (is_builtin(exec.cmd_args[0]) && !has_next_pipe)
		{
			execute_builtin(mshell, exec.cmd_args);
			ast = ast->next_right;
			continue;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			return;
		}
		if (pid == 0) // CHILD PROCESS STARTS HERE
		{
			//INPUT SET UP - DUP

			if (exec.temp_fd[FD_IN] != STDIN_FILENO)
				dup2(exec.temp_fd[FD_IN], STDIN_FILENO); // redir stdin to infile
			else if (prev_fd != STDIN_FILENO)
				dup2(prev_fd, STDIN_FILENO); //redir current command's standard input
											//(stdin) to come from the read end of the previous pipe.

			//OUTPUT SETUP - DUPPING
			if (exec.temp_fd[FD_OUT] != STDOUT_FILENO)
				dup2(exec.temp_fd[FD_OUT], STDOUT_FILENO); //NEED CHECK DUP STATUS
			else if (has_next_pipe)
				dup2(pipefd[1], STDOUT_FILENO);

			//CHECK UNUSED AND CLOSE!
			if (exec.temp_fd[FD_IN] != STDIN_FILENO)
				close(exec.temp_fd[FD_IN]); //NEED CHECK CLOSE STATUS
			if (exec.temp_fd[FD_OUT] != STDOUT_FILENO)
				close(exec.temp_fd[FD_OUT]);
			if (prev_fd != STDIN_FILENO)
				close(prev_fd);
			if (has_next_pipe)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			//printf("%s\n", get_token_type_name(node->type));
			if (is_builtin(exec.cmd_args[0]))
			{
				execute_builtin(mshell, exec.cmd_args);
				delete_minishell(mshell);
				exit(mshell->exitcode);
			}
			if (cmd_node == NULL)
			{
				ft_dprintf(2, "minishell: command node not found\n");
				exit(127);
			}
			// for (int i = 0; ast->cmd[i]; i++)
			// {
			// 	stdout = stderr;
			// 	printf("[%i]: %s\n", i, ast->cmd[i]);
			// }
			external_cmd = get_command_argv(mshell, cmd_node); //cmd_node == current node as a command
			execve(external_cmd[0], exec.cmd_args, mshell->envp->envp);
			perror(external_cmd[0]);
			ft_free_2d(external_cmd);
			arena_destroy(&mshell->arena);
			exit(127);
			//if executable file exists but no permission --> 126
		}
		else //BACK TO PARENTS, after forking a child to handle a command in a pipeline
		{

			mshell->command_count++;
			mshell->last_pid = pid; //storing current last pid
			//prev_fd is the readend of the previous pipe, used as stdin of curr cmd
			//parent no need this so we close!
			if (prev_fd != STDIN_FILENO)
				close(prev_fd);

			// exec.temp_fd[FD_IN] holds input redir <infile or heredoc, must close now
			if (exec.temp_fd[FD_IN] != STDIN_FILENO)
				close(exec.temp_fd[FD_IN]);

			// exec.temp_fd[FD_OUT] holds output redir >outf >>file, must close now
			if (exec.temp_fd[FD_OUT] != STDOUT_FILENO)
				close(exec.temp_fd[FD_OUT]);

			if (has_next_pipe)
			{
				close(pipefd[1]); //parents dont write shit
				prev_fd = pipefd[0]; //pass read end to next cmd!
			}
		}
		ast = ast->next_right;
	}
	mshell->exitcode = wait_for_children(mshell);
}
