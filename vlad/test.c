#include <strings.h>
#include <stdio.h>
#include "../lib/libft/inc/libft.h"

static int	is_separator(char c)
{
	return(c == '<' || c == '>' || c == '|' || c == '<' || c == '\'' || c == '\"' || ft_isspace(c));
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '<');
}

int	inquotes(char c, int *in_double, int *in_single)
{
	// printf("[BEFORE] Char: %c | in_single: %d | in_double: %d\n", c, *in_single, *in_double);
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (c == '"' && !*in_single)
		*in_double = !*in_double;
	return (*in_double || *in_single);
}

char	*set_quotes_around_operators_in_quotes(const char *str)
{
	int	i;
	int	in_single;
	int	in_double;
	int	in_quotes;
	char	*new;
	char	*temp;

	char additive[6];
	i = 0;
	in_single = 0;
	in_double = 0;
	new = ft_strdup("");
	while (str[i])
	{
		in_quotes = inquotes(str[i], &in_double, &in_single);
		if (is_operator(str[i]) && in_quotes)
		{
			if (in_double == 1)
			{
				additive[0] = '\"';
				additive[1] = '\"';
				additive[2] = str[i];
				additive[3] = '\"';
				additive[4] = '\"';
				additive[5] = '\0';
			}
			else if (in_single == 1)
			{
				additive[0] = '\'';
				additive[1] = '\'';
				additive[2] = str[i];
				additive[3] = '\'';
				additive[4] = '\'';
				additive[5] = '\0';
			}
			temp = new;
			new = ft_strjoin(new, additive);
			free (temp);
			temp = NULL;
		}
		else
		{
			char additive[2] = {str[i], '\0'};
			temp = new;
			new = ft_strjoin(new, additive);
			free (temp);
			temp = NULL;
		}
		i++;
	}
	return (new);
}

char	*set_quotes_around_non_quoted_words(char *new)
{
	int		i;
	int		in_single;
	int		in_double;
	int		in_quotes;
	char	*temp;

	in_single = 0;
	in_double = 0;
	i = 0;
	char *new2 = ft_strdup("");
	if (!is_separator(new[i]))
	{
		char additive[3] = {'\"', new[i], '\0'};
		temp = new;
		new = ft_strjoin(new, additive);
		free (temp);
		temp = NULL;
		i++;
	}
	while (new[i])
	{
		in_quotes = inquotes(new[i], &in_double, &in_single);
		if (is_separator(new[i]) && !is_separator(new[i + 1]) && !in_quotes && new[i + 1] != '\0')
		{
			char additive[3] = {new[i], '\"', '\0'};
			temp = new2;
			new2 = ft_strjoin(new2, additive);
			free (temp);
			temp = NULL;
		}
		else if (!is_separator(new[i]) && is_separator(new[i + 1]) && !in_quotes)
		{
			char additive[3] = {new[i], '\"', '\0'};
			temp = new2;
			new2 = ft_strjoin(new2, additive);
			free (temp);
			temp = NULL;
		}
		else
		{
			char additive[2] = {new[i], '\0'};
			temp = new2;
			new2 = ft_strjoin(new2, additive);
			free (temp);
			temp = NULL;
		}
		i++;
	}
	return (new2);
}

char	*remove_adjacent_quotes(char *new2)
{
	int		i;
	int		in_single;
	int		in_double;
	int		in_quotes;
	char	*temp;

	in_single = 0;
	in_double = 0;
	i = 0;
	char *new3 = ft_strdup("");
	while (new2[i])
	{
		in_quotes = inquotes(new2[i], &in_double, &in_single);
		if (is_quote(new2[i]) && is_quote(new2[i + 1]) && !in_quotes)
		{
			i++;
			in_quotes = inquotes(new2[i], &in_double, &in_single);
		}
		else
		{
			char additive[2] = {new2[i], '\0'};
			temp = new3;
			new3 = ft_strjoin(new3, additive);
			free (temp);
			temp = NULL;
		}
		i++;
	}
	return(new3);
}

char	*con(const char *str)
{
	// char	*new0;
	char	*new;
	char	*new2;
	char	*new3;
	new = set_quotes_around_operators_in_quotes(str);
	new2 = set_quotes_around_non_quoted_words(new);
	free (new);
	printf("new2: 	   %s\n", new2);
	new3 = remove_adjacent_quotes(new2);
	free (new2);
	return (new3);
}


int main()
{
	// char str[] = "\"asd\"";
	char str[] = "<asd\'as<<da<sd\'<123> | asdsad \'12\'fd\"s<<\'\'d\"\"asd\"";
	printf("original:  %s\n", str);
	char *str2 = con(str);
	printf("new3: 	   %s\n", str2);
	printf("should be: <\"asdas<<da<sd\"<\"123\"> | \"asdsad\" \"12fds<<\'\'dasd\"\n");
	free (str2);
}
