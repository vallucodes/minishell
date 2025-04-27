/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:45:48 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/27 14:04:44 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_heredoc_input(t_minishell *mshell,
			int *fd_tmp, int *fd_stdin, char **file)
{
	sig_action_heredoc(mshell);
	*fd_stdin = get_stdin(mshell);
	*file = create_tmp_file(mshell, fd_tmp);
	mshell->rl_count_heredoc = 0;
}

static char	*read_heredoc_input(t_minishell *mshell, char *eof, t_expand expand)
{
	char	*input;
	char	*file;
	int		fd_tmp;
	int		fd_stdin;

	init_heredoc_input(mshell, &fd_tmp, &fd_stdin, &file);
	while (1)
	{
		input = readline("> ");
		if (g_signal == SIGINT)
			return (cleanup_at_signal(mshell, &input, fd_stdin, fd_tmp), NULL);
		if (!input)
		{
			print_warning(mshell->rl_count, eof);
			break ;
		}
		mshell->rl_count_heredoc += 1;
		if (is_eof(eof, input))
			break ;
		save_line_to_tmp_file(mshell, input, fd_tmp, expand);
		free_and_set(&input);
	}
	cleanup_at_success(mshell, &input, &fd_tmp, &fd_stdin);
	return (file);
}

static void	replace_token(t_token *current, char *file)
{
	current->value++;
	current->len = 1;
	current->type = REDIR_IN;
	current->next->type = FILE_TOKEN;
	current->next->value = file;
	current->next->len = ft_strlen(file);
}

static int	check_quotes(t_minishell *mshell, t_token *current)
{
	t_quotes_helper	quotes;
	char			*new_str;
	char			*input_str;
	size_t			i;
	char			expansion_flag;

	expansion_flag = EXPAND;
	input_str = current->value;
	init_quotes(&quotes);
	new_str = ft_arena_strdup(mshell->arena, "");
	if (!new_str)
		exit_cleanup_error(mshell, "malloc");
	i = 0;
	while (input_str[i])
	{
		update_quote_state(input_str[i], &quotes);
		if (quotes.in_quotes)
			expansion_flag = DONT_EXPAND;
		if (!there_is_quote_state_change(quotes))
			append_char(mshell, input_str, &new_str, i);
		i++;
	}
	replace_content_of_token(current, new_str);
	return (expansion_flag);
}

int	handle_heredoc(t_minishell *mshell, t_token *tokens)
{
	t_token		*current;
	char		*file;
	t_expand	expnd_flag;

	expnd_flag = EXPAND;
	current = tokens;
	while (current)
	{
		if (current->type == HERE_DOC)
		{
			expnd_flag = check_quotes(mshell, current->next);
			file = read_heredoc_input(mshell, current->next->value, expnd_flag);
			if (file == NULL)
				return (FAIL);
			replace_token(current, file);
		}
		current = current->next;
	}
	return (SUCCESS);
}
