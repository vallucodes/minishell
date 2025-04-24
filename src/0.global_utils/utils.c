#include "minishell.h"

void	append_char(t_minishell *mshell, char *src, char **dst, size_t i)
{
	char	additive[2];

	additive[0] = src[i];
	additive[1] = '\0';
	*dst = ft_arena_strjoin(mshell->arena, *dst, additive);
	if (!*dst)
		exit_cleanup_error(mshell, "malloc");
}

int	is_any_redirect(t_token *current)
{
	return (current->type == REDIR_IN
			|| current->type == REDIR_OUT
			|| current->type == REDIR_APPEND
			|| current->type == HERE_DOC);
}

void	replace_content_of_token(t_token *current, char *new_str)
{
	current->value = new_str;
	current->len = ft_strlen(new_str);
}
