#include "../../inc/minishell.h"

// is it a valid variable name for unset?
static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0] || ft_isdigit(str[0]) || str[0] == '=') //cannot start with '='
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_') //every character must be alphanumeric or an underscore
			return (0);
		i++;
	}
	return (1);
}

//lets match input & env key
static int match_env_key(const char *env_entry, const char *key)
{
	int result;
	size_t key_len = ft_strlen(key);

	int match = ft_strncmp(env_entry, key, key_len);
	if (match == 0 && env_entry[key_len] == '=') //last char must be =
		return (1);
	else
		return (0);
}

//remove env var when match is found
//find the match position, free the match then left shift everything after that
//
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

int	ft_unset(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			remove_env_var(env, args[i]);
		else
			ft_dprintf(STDERR_FILENO, "minishell: unset: `%s': not a valid identifier\n", args[i]);
		i++;
	}
	return (0);
}

