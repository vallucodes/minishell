// #include "../inc/minishell.h"

// static int	is_operator(char c)
// {
// 	return (c == '<' || c == '>' || c == '|' || c == '<');
// }

// void	concatinate_adjacecnt_quotes(char *str)
// {
// 	int	i;
// 	int	in_quotes;
// 	char	*new;

// 	i = 0;
// 	in_quotes = 0;
// 	new = ft_strdup("");
// 	while (str[i])
// 	{
// 		if (!is_operator(str[i]))
// 			ft_strjoin(new, str[i]);
// 		i++;
// 	}
// 	return (new);
// }
