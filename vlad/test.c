#include <strings.h>
#include <stdio.h>
#include "../lib/libft/inc/libft.h"

static int	is_separator(char c)
{
	return(c == '<' || c == '>' || c == '|' || c == '<' || c == '\'' || c == '\"' || ft_isspace(c));
}

static int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '<');
}

char	*con(char *str)
{
	int	i;
	int	in_single;
	int	in_double;
	int	in_quotes;
	char	*new;

	i = 0;
	in_single = 0;
	in_double = 0;
	in_quotes = 0;
	new = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		if (is_operator(str[i]) && (in_double || in_single))
		{
			char additive[6] = {'\"', '\"', str[i], '\"' ,'\"', '\0'};
			new = ft_strjoin(new, additive);
		}
		else
		{
			char additive[2] = {str[i], '\0'};
			new = ft_strjoin(new, additive);
		}
		i++;
	}
	i = 0;
	printf("new: 	   %s\n", new);
	char *new2 = ft_strdup("");
	if (!is_separator(new[i]))
	{
		char additive[3] = {'\"', str[i], '\0'};
		new = ft_strjoin(new, additive);
		i++;
	}
	while (new[i])
	{
		if (new[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (new[i] == '"' && !in_single)
			in_double = !in_double;
		in_quotes = in_double || in_single;
		if (is_separator(new[i]) && !is_separator(new[i + 1]) && !in_quotes && new[i + 1] != '\0')
		{
			char additive[3] = {new[i], '\"', '\0'};
			new2 = ft_strjoin(new2, additive);
		}
		else if (!is_separator(new[i]) && is_separator(new[i + 1]) && !in_quotes)
		{
			char additive[3] = {new[i], '\"', '\0'};
			new2 = ft_strjoin(new2, additive);
		}
		else
		{
			char additive[2] = {new[i], '\0'};
			new2 = ft_strjoin(new2, additive);
		}
		i++;
	}
	return (new2);
}


int main()
{
	// char str[] = "\"asd\"";
	char str[] = "<asd\"as<dasd\"<123> | asdsad fd'sd'\"asd\"";
	printf("original:  %s\n", str);
	printf("new2: 	   %s\n", con(str));
	printf("should be: <\"asdas<dasd\"<\"123\"> | \"asdsad\" \"fdsdasd\"\n");
}
