/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:45:33 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 16:45:34 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer(t_minishell *mshell, t_input *input)
{
	init_lexer(input, mshell->input_str);
	create_tokens(mshell, input);
	if (tokens_validation(mshell, input->tokens) == FAIL)
	{
		free(mshell->input_str);
		arena_delete(&mshell->arena);
		return (FAIL);
	}
	retokenize_words(input->tokens);
	return (SUCCESS);
}
