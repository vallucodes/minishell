#include "../../inc/minishell.h"
#include "../../inc/builtin.h"


// -------------------- MAIN TEST --------------------
int	ft_strtestcmp( char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	i = 0;
	while (str1[i] == str2[i] && str1[i])
		i++;
	return (str1[i] - str2[i]);
}
// -------------------- end TEST --------------------

int execute_builtin(t_minishell *mshell, t_ast_test *ast)
{
	if (!ast || !ast->cmd || !ast->cmd[0])
		return (FAIL);

	printf("DEBUG: cmd[0] in exe_built = %s\n", ast->cmd[0]);
	printf("DEBUG: strcmp = %d\n", ft_strtestcmp(ast->cmd[0], "env"));

	if (ft_strcmp(ast->cmd[0], "env") == 0)
	{
		mshell->exitcode = ft_env(mshell->envp, &ast->cmd[1]);
		//printf ("go in this loop");
		//fprintf(stderr, "[builtin env exit code: %d]\n", mshell->exitcode);
		return (mshell->exitcode);
	}
	return (0);

}

