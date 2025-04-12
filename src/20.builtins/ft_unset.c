#include "../../inc/minishell.h"

static void	remove_env_var(t_env *env, const char *key);

int	ft_unset(char **args, t_env *env)
{
	int	i;

	i = 1; //skip "unset"
	while (args[i])
	{
		if (is_valid_identifier_range(args[i], ft_strlen(args[i])))
			remove_env_var(env, args[i]);
		else
			ft_dprintf(2, "Giraffeshell: unset: `%s': not a valid identifier\n", args[i]);
		i++;
	}
	return (0);
}

//remove env var when match is found
//find the match position, free the match then left shift everything after that
static void	remove_env_var(t_env *env, const char *key)
{
	unsigned int	cur_index;
	unsigned int	shift_left;

	cur_index = 0;
	while (cur_index < env->len)
	{
		if(match_env_key(env->envp[cur_index], key))
		{
			free(env->envp[cur_index]);
			shift_left = cur_index;
			while (shift_left < env->len - 1)
			{
				env->envp[shift_left] = env->envp[shift_left + 1];
				shift_left++;
			}
			env->envp[env->len - 1] = NULL;
			env->len--;
			return;
		}
		cur_index++;
	}
}
