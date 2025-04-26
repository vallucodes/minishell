/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:45:21 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 16:45:22 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	quote_validation(char *input, t_quotes type, bool *balanced)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (type == NONE)
		{
			if (input[i] == '\'')
				i += quote_validation(&input[i + 1], SINGLE, balanced);
			if (input[i] == '"')
				i += quote_validation(&input[i + 1], DOUBLE, balanced);
		}
		else if (type == SINGLE || type == DOUBLE)
		{
			if (input[i] == '\'' && type == SINGLE)
				return (i + 1);
			else if (input[i] == '"' && type == DOUBLE)
				return (i + 1);
		}
		i++;
	}
	if (type == SINGLE || type == DOUBLE)
		*balanced = 0;
	return (i);
}

int	input_validation(t_minishell *mshell)
{
	bool	balanced;

	balanced = 1;
	if (ft_strlen(mshell->input_str) > 8191)
	{
		print_error(LINE_TOO_LONG, NULL, 0);
		mshell->exitcode = 2;
		return (FAIL);
	}
	if (!mshell->input_str || ft_is_all_whitespace(mshell->input_str))
		return (FAIL);
	quote_validation(mshell->input_str, NONE, &balanced);
	if (!balanced)
	{
		print_error(BALANCE, NULL, 0);
		mshell->exitcode = 2;
		return (FAIL);
	}
	return (SUCCESS);
}
