#include "../inc/minishell.h"

static void	init_vars(size_t *i, char **input_str, \
		t_token *current, t_quotes_helper *quotes)
{
	*i = 0;
	init_quotes(quotes);
	*input_str = current->value;
}

static void	find_and_set_next_command(t_token *current)
{
	current = current->next;
	while (current)
	{
		if (current->type == ARG)
		{
			current->type = COMMAND;
			return ;
		}
		current = current->next;
	}
}

static void	delete_token(t_input *input, t_token *current, t_token *previous)
{
	if (current->type == COMMAND)
		find_and_set_next_command(current);
	if (previous)
		previous->next = current->next;
	else
	{
		current->type = 0;
		input->tokens = current->next;
	}
}
static bool	is_ambiguous_redirect(t_minishell *mshell, t_token *current, char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**env;

	if (current->type != FILE_TOKEN)
		return (0);
	env = mshell->envp->envp;
	len = get_len_explandeble(str);
	i = -1;
	while (env[++i])
	{
		if (expandable_exists(len, env, i, str))
		{
			j = skip_to_start_of_expandable(env[i]);
			if (env[i][j] == '\0') // variable is empty like "$haha" = ""
			{
				current->ambiguous = 1;
				return (1);
			}
			while (env[i][j])
			{
				if (current && ft_isspace(env[i][j]))
				{
					current->ambiguous = 1;
					return (1);
				}
				j++;
			}
			return (0);
		}
	}
	if (env[i] == NULL)
	{
		current->ambiguous = 1;
		return (1);
	}
	return (0);
}

static void	loop_through_word(t_minishell *mshell, t_input *input, t_token *current, t_token *previous)
{
	t_quotes_helper	quotes;
	char			*new_str;
	char			*input_str;
	size_t			i;
	bool			is_only_env_expandable;

	is_only_env_expandable = 1;
	init_vars(&i, &input_str, current, &quotes);
	new_str = ft_arena_strdup(mshell->arena, "");
	if (!new_str)
		exit_cleanup_error(mshell, "malloc");
	while (input_str[i])
	{
		update_quote_state(input_str[i], &quotes);
		if (is_valid_expandable(quotes, &input_str[i]) && !is_ambiguous_redirect(mshell, current, &input_str[i]))
			i += expand_content(mshell, current, &input_str[i], 0, &new_str);
		else if (is_pid_expansion(quotes, &input_str[i]))
		{
			is_only_env_expandable = 0;
			i += expand_pid(mshell, 0, &new_str);
		}
		else if (is_exitcode_expansion(quotes, &input_str[i]))
		{
			is_only_env_expandable = 0;
			i += expand_exitcode_value(mshell, 0, &new_str);
		}
		else if (there_is_quote_state_change(quotes))
		{
			is_only_env_expandable = 0;
			i++;
		}
		else
		{
			is_only_env_expandable = 0;
			append_char(mshell, input_str, &new_str, i++);
		}
	}
	if (new_str[0] == '\0' && is_only_env_expandable == 1 && (current->type == COMMAND || current->type == ARG))
		delete_token(input, current, previous);
	else
		replace_content_of_token(current, new_str);
}

void	expand_remove_quotes(t_minishell *mshell, t_input *input)
{
	t_token	*current;
	t_token	*previous;

	current = input->tokens;
	previous = NULL;
	while (current)
	{
		if (is_any_word(current->type))
			loop_through_word(mshell, input, current, previous);
		if (current->type != 0)
			previous = current;
		current = current->next;
	}
}
