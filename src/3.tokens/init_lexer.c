/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:45:26 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 16:45:27 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_lexer(t_input *new_input, char *input_str)
{
	new_input->full_str = input_str;
	new_input->index = 0;
	new_input->len = ft_strlen(input_str);
	new_input->tokens = NULL;
}
