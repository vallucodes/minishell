/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:18:46 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 21:18:54 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_env
{
	char			**envp;
	unsigned int	allocated_capacity;
	unsigned int	len;

}	t_env;

int		copy_env(t_env **env, char **envp);
int		match_env_key(const char *env_entry, const char *key);
char	*get_env_value(char **envp, const char *key);
int		realloc_env_capacity(t_env *env);
char	**dup_and_sort_env(t_env *env);
void	free_env(t_env *env);
void	exit_env(char *msg, t_env **env);
void	free_partial_env(char **envp, int up_to);

#endif
