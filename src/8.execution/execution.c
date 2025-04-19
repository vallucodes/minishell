#include "../../inc/minishell.h"
#include <sys/wait.h>
#include <sys/stat.h>

// static int	execute_in_sub_process(t_minishell *mshell, t_ast *ast)
// {
// 	fork
// 	run all commands in each process


// 	exe external
// 	execve
// 	return waitAll();
// }


// static int	wait_all(t_minishell *mshell)
// {
// 	int	exitCode;

// 	while (condition)
// 	{
// 		/* code */
// 	}

// }

t_ast *get_cmd_node(t_ast *ast)
{
	while (ast)
	{
		if (ast->type == COMMAND)
			return (ast);
		ast = ast->next_left;
	}
	return (NULL);
}


static int execute_builtin_alone(t_minishell *mshell, t_ast *ast)
{
	if (handle_redirection(ast) < 0)
		return (FAIL);

	mshell->exitcode = execute_builtin(mshell, ast);
	if (dup2(mshell->origin_stdin, STDIN_FILENO) < 0 || dup2(mshell->origin_stdout, STDOUT_FILENO) < 0)
		return (FAIL);
	return (0);
}


void execute_ast_v1(t_minishell *mshell, t_ast *ast)
{
	if (ast->type != PIPE && is_builtin(ast))
		mshell->exitcode = execute_builtin_alone(mshell, ast);
	// else
	// 	mshell->exitcode = execute_in_sub_process(mshell, ast);
	//setup pipe if have

	//execute command builtin in parent, do redeirection and restore std if needed


	// if (not_builtin || more than 2 commands)
	// 	fork();

	// 	handle_redirection();
	// 	execute command()

}
