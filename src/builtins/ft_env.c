#include "../../inc/minishell.h"

int ft_env(t_env *my_env, char **args)
{
	unsigned int	i;

	if (!my_env || !my_env->envp)
		return (FAIL);

	if (args && args[0])
	{
		dprintf(STDERR_FILENO, "env: too many arguments\n");
		return (1);
	}

	i = 0;
	while(i < my_env->len)
	{
		if (my_env->envp[i] && (ft_strchr(my_env->envp[i], '=')))
			printf("%s\n", my_env->envp[i]);
		i++;
	}
	return (0);
}
