/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena_calloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:44:39 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 16:44:40 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*ft_arena_calloc(t_arena *a, size_t nmemb, size_t size, int alignment)
{
	void	*ptr;
	size_t	result;

	result = nmemb * size;
	if (nmemb && size != result / nmemb)
		return (NULL);
	ptr = arena_alloc(a, nmemb * size, alignment);
	if (ptr != NULL)
		ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
