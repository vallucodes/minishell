#include "../../inc/minishell.h"

static void	sort_strings_tab(char **arr, int len);

char	**dup_and_sort_env(t_env *env)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (env->len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < (int)env->len)
	{
		copy[i] = ft_strdup(env->envp[i]);
		if (!copy[i])
		{
			ft_free_2d(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	sort_strings_tab(copy, env->len);
	return (copy);
}

static void	sort_strings_tab(char **arr, int len)
{
	int		i;
	char	*temp;

	i = 0;
	while (i < len - 1)
	{
		if (ft_strcmp(arr[i], arr[i + 1]) > 0)
		{
			temp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}
