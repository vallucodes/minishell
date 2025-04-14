#include "minishell.h"

void	append_char(char *str, char **new, int i)
{
	char	*temp;
	char	additive[2];

	additive[0] = str[i];
	additive[1] = '\0';
	temp = *new;
	*new = ft_strjoin(*new, additive);
	free (temp);
}

int	is_any_redirect(t_token *current)
{
	return(current->type == REDIRECT_IN ||
			current->type == REDIRECT_OUT ||
			current->type == REDIRECT_APPEND ||
			current->type == HERE_DOCUMENT);
}

void	replace_content_of_token(t_token *current, char *new_str)
{
	current->value = new_str;
	current->len = ft_strlen(new_str);
}
