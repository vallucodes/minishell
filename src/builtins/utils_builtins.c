#include "../../inc/minishell.h"

int count_cmds(char **cmds)
{
	int count = 0;
	while (cmds && cmds[count])
		count++;
	return count;
}

// is it a valid variable name for unset & export?
int	is_valid_identifier_range(const char *str, size_t len)
{
	size_t i = 0;

	if (!str || len == 0 || ft_isdigit(str[0]) || str[0] == '=')
		return (0);

	while (i < len)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

//lets match input & env key
int match_env_key(const char *env_entry, const char *key)
{
	int		result;
	size_t	key_len;
	int		match;

	key_len = ft_strlen(key);
	match = ft_strncmp(env_entry, key, key_len);
	if (match == 0 && (env_entry[key_len] == '=' || env_entry[key_len] == '\0')) //last char must be = OR \0
		return (1);
	else
		return (0);
}

//realloc when theres not enough space in allocated memory
int realloc_env_capacity(t_env *env)
{
	size_t	new_capacity;
	char	**new_envp;
	size_t	i;

	if (env->len + 1 < env->allocated_capacity)
		return (1);
	new_capacity = env->allocated_capacity * 2;
	if (new_capacity == 0)
		new_capacity = 8; //just in case new capa is 0 then 0 cant *2
	new_envp = malloc(sizeof(char *) * (new_capacity + 1));
	if (!new_envp)
		return (0);
	i = 0;
	while (i < env->len)
	{
		new_envp[i] = env->envp[i];
		i++;
	}
	free(env->envp);
	env->envp = new_envp;
	env->allocated_capacity = new_capacity;
	return (1);
}
