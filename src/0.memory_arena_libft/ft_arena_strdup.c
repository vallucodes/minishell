/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena_strdup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:54:48 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/15 18:40:38 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_arena_strdup(t_arena *a, const char *s)
{
	char	*dst;
	size_t	len;
	int		i;

	len = ft_strlen(s) + 1;
	dst = arena_alloc(a, len * sizeof(char), alignof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}
