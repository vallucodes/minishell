/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:02:27 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 21:50:23 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_sorted_export(t_env *env);
static int	handle_export_arg(t_minishell *mshell, char *arg);
static int	export_update_or_add(t_minishell *mshell, char *arg, size_t key_len,
				int key_has_value);

int	ft_export(char **args, t_minishell *mshell)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (!args[i])
		return (print_sorted_export(mshell->envp), 0);
	while (args[i])
	{
		if (handle_export_arg(mshell, args[i]) == FAIL)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}

static void	print_sorted_export(t_env *env)
{
	size_t	key_len;
	char	**sorted;
	size_t	i;
	char	*equal;

	i = 0;
	sorted = dup_and_sort_env(env);
	while (sorted && sorted[i])
	{
		equal = ft_strchr(sorted[i], '=');
		if (equal)
		{
			key_len = equal - sorted[i];
			ft_dprintf(STDOUT_FILENO, "declare -x ");
			write(STDOUT_FILENO, sorted[i], key_len + 1);
			ft_dprintf(STDOUT_FILENO, "\"%s\"\n", equal + 1);
		}
		else
		{
			ft_dprintf(STDOUT_FILENO, "declare -x %s\n", sorted[i]);
		}
		i++;
	}
	ft_free_2d(sorted);
}

static int	handle_export_arg(t_minishell *mshell, char *arg)
{
	char	*equal_sign;
	size_t	key_len;
	int		key_has_value;

	equal_sign = ft_strchr(arg, '=');
	key_has_value = (equal_sign != NULL);
	if (key_has_value)
		key_len = (size_t)(equal_sign - arg);
	else
		key_len = ft_strlen(arg);
	if (!is_valid_identifier_range(arg, key_len))
	{
		ft_dprintf(2, "Giraffeshell: export: `%s`: not a valid identifier\n",
			arg);
		return (FAIL);
	}
	if (export_update_or_add(mshell, arg, key_len, key_has_value) == FAIL)
	{
		ft_dprintf(2, "Giraffeshell: export: `%s`: add update fails\n", arg);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	export_update_or_add(t_minishell *mshell, char *arg, size_t key_len,
		int key_has_value)
{
	char	*key;

	key = ft_substr(arg, 0, key_len);
	if (!key)
	{
		ft_dprintf(2, "Giraffeshell: export: malloc failed\n");
		return (FAIL);
	}
	if (update_var_env(mshell->envp, arg, key, key_has_value) == FAIL)
	{
		if (add_var_to_env(mshell->envp, arg) == FAIL)
		{
			perror("malloc");
			delete_minishell(mshell);
			free(key);
			exit(1);
		}
	}
	free(key);
	return (SUCCESS);
}
