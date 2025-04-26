/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:04:47 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 21:04:49 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv && argv[count])
		count++;
	return (count);
}

int	is_valid_identifier_range(const char *str, size_t len)
{
	size_t	i;

	i = 0;
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

int	update_var_env(t_env *env, const char *arg, const char *key,
		int key_has_value)
{
	size_t	i;

	i = 0;
	while (i < env->len)
	{
		if (match_env_key(env->envp[i], key))
		{
			if (key_has_value)
			{
				free(env->envp[i]);
				env->envp[i] = ft_strdup(arg);
				if (!env->envp[i])
					return (FAIL);
			}
			return (SUCCESS);
		}
		i++;
	}
	return (FAIL);
}

int	add_var_to_env(t_env *env, const char *arg)
{
	if (realloc_env_capacity(env) == FAIL)
		return (FAIL);
	env->envp[env->len] = ft_strdup(arg);
	if (!env->envp[env->len])
		return (FAIL);
	env->len++;
	env->envp[env->len] = NULL;
	return (SUCCESS);
}
