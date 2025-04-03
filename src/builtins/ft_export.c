#include "../../inc/minishell.h"


void		print_sorted_export(t_env *env);
static int	handle_export_arg(t_env *env, char *arg);
static int	export_update_or_add(t_env *env, char *arg, size_t key_len, int has_value);
static int	export_update(t_env *env, const char *arg, const char *key, int has_value);
static int	export_add(t_env *env, const char *arg, const char *key, size_t key_len, int has_value);

int	ft_export(char **args, t_env *env)
{
	int i = 1;
	int exit_code = 0;

	if (!args[i])
		return (print_sorted_export(env), 0);
	while (args[i])
	{
		if (!handle_export_arg(env, args[i]))
			exit_code = 1;
		i++;
	}
	return (exit_code);
}


void	print_sorted_export(t_env *env)
{
	char **sorted = dup_and_sort_env(env);
	size_t i = 0;

	while (sorted && sorted[i])
	{
		printf("declare -x %s\n", sorted[i]);
		i++;
	}
	ft_free_2d(sorted);
}

static int	handle_export_arg(t_env *env, char *arg)
{
	char	*equal_sign;
	size_t	key_len;
	int		has_value;

	equal_sign = ft_strchr(arg, '=');
	has_value = (equal_sign != NULL);
	if (has_value)
		key_len = (size_t)(equal_sign - arg);
	else
		key_len = ft_strlen(arg);
	if (!is_valid_identifier_range(arg, key_len))
	{
		ft_dprintf(2, "minishell: export: `%s`: not a valid identifier\n", arg);
		return (0); // invalid
	}
	if (!export_update_or_add(env, arg, key_len, has_value))
		return (0); // malloc fail
	return (1);
}

static int	export_update_or_add(t_env *env, char *arg, size_t key_len, int has_value)
{
	char *key = ft_substr(arg, 0, key_len);
	if (!key)
	{
		ft_dprintf(2, "minishell: export: malloc failed\n");
		return (0);
	}
	if (!export_update(env, arg, key, has_value))
	{
		if (!export_add(env, arg, key, key_len, has_value))
		{
			free(key);
			return (0);
		}
	}
	free(key);
	return (1);
}

static int	export_update(t_env *env, const char *arg, const char *key, int has_value)
{
	size_t i = 0;

	while (i < env->len)
	{
		if (match_env_key(env->envp[i], key))
		{
			if (has_value)
			{
				free(env->envp[i]);
				env->envp[i] = ft_strdup(arg);
			}
			return (1); // key found
		}
		i++;
	}
	return (0); // not found
}

static int	export_add(t_env *env, const char *arg, const char *key, size_t key_len, int has_value)
{
	if (!realloc_env_capacity(env))
	{
		ft_dprintf(2, "minishell: export: malloc failed\n");
		return (0);
	}
	if (has_value)
	{
		env->envp[env->len] = ft_strdup(arg);
		if (!env->envp[env->len])
			return (0);
		env->len++;
	}
	else
	{
		char *new_var = malloc(key_len + 2);
		if (!new_var)
		{
			ft_dprintf(2, "minishell: export: malloc failed\n");
			return (0);
		}
		ft_memcpy(new_var, key, key_len);
		new_var[key_len] = '\0';
		env->envp[env->len++] = new_var;
	}
	env->envp[env->len] = NULL;
	return (1);
}




//check if have place in env allocated_space
	//if have, then just export proceed
	//if no, reallocate

//export
	//random bullshit: bash: export: `53478957395': not a valid identifier
	// if value exists -> ust change valiue fir


// when type export
// # shows MYVAR= and sorted in export list
// when type env
// # does NOT show MYVAR
