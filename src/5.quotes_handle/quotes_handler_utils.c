/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:45:53 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 20:34:45 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_valid_expandable(t_quotes_helper quotes, char *input_str)
{
	return (!quotes.in_single && input_str[0] == '$'
		&& is_valid_char_expansion(input_str[1]));
}

bool	there_is_quote_state_change(t_quotes_helper quotes)
{
	return (quotes.previous_in_quotes != quotes.in_quotes);
}

bool	is_any_word(t_token_type type)
{
	return ((type == COMMAND) || (type == ARG) || (type == FILE_TOKEN));
}

bool	expandable_exists(int len, char **env, size_t i, char *str)
{
	return ((ft_strncmp(&env[i][0], &str[1], len - 1) == 0) &&
		(env[i][len - 1] == '='));
}

bool	is_exp_is_empty_is_bare_is_cmd_or_arg(t_vars vars, t_token *curr)
{
	return (vars.new_str[0] == '\0' && vars.is_bare_exp == 1
		&& (curr->type == COMMAND || curr->type == ARG));
}
