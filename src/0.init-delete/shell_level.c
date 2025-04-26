/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:57:16 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 21:57:18 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_shlvl_entry(t_env *env)
{
	char	*old_value;
	int		shlvl;
	char	*new_value;
	char	*new_entry;

	old_value = get_env_value(env->envp, "SHLVL");
	if (old_value)
		shlvl = ft_atoi(old_value) + 1;
	else
		shlvl = 1;
	new_value = ft_itoa(shlvl);
	if (!new_value)
		exit_env("malloc", &env);
	new_entry = ft_strjoin("SHLVL=", new_value);
	free(new_value);
	if (!new_entry)
		exit_env("malloc", &env);
	return (new_entry);
}

void	increment_shlvl(t_env *env)
{
	char	*new_entry;
	size_t	i;

	new_entry = create_shlvl_entry(env);
	i = 0;
	while (i < env->len)
	{
		if (match_env_key(env->envp[i], "SHLVL"))
		{
			free(env->envp[i]);
			env->envp[i] = new_entry;
			return ;
		}
		i++;
	}
	if (realloc_env_capacity(env) == FAIL)
		exit_env("malloc", &env);
	env->envp[env->len] = new_entry;
	env->len++;
	env->envp[env->len] = NULL;
}
