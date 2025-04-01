#include "../../inc/minishell.h"
#include "../../inc/builtin.h"

// -------------------- end TEST --------------------

int execute_builtin(t_minishell *mshell, t_ast *ast)
{
	if (!ast || !ast->cmd || !ast->cmd[0])
		return (FAIL);

	if (ft_strcmp(ast->cmd[0], "env") == 0)
	{
		mshell->exitcode = ft_env(mshell->envp, &ast->cmd[1]);
		//printf ("go in this loop");
		//fprintf(stderr, "[builtin env exit code: %d]\n", mshell->exitcode);
		return (mshell->exitcode);
	}

}

