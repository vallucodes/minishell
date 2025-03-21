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

char	*con(char *str)
{
	int	i;
	int	in_single;
	int	in_double;
	int	in_quotes;
	char	*new;
	char	*temp;

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


	in_single = 0;
	in_double = 0;
	i = 0;
	char *new2 = ft_strdup("");
	if (!is_separator(new[i]))
	{
		char additive[3] = {'\"', str[i], '\0'};
		temp = new;
		new = ft_strjoin(new, additive);
		free (temp);
		temp = NULL;
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
	free (new);


	in_single = 0;
	in_double = 0;
	i = 0;
	char *new3 = ft_strdup("");
	while (new2[i])
	{
		if (new2[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (new2[i] == '"' && !in_single)
			in_double = !in_double;
		in_quotes = in_double || in_single;
		if (is_quote(new2[i]) && is_quote(new2[i + 1]) && !in_quotes)
		{
			i++;
			if (new2[i] == '\'' && !in_double)
				in_single = !in_single;
			else if (new2[i] == '"' && !in_single)
				in_double = !in_double;
			in_quotes = in_double || in_single;
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
	free (new2);
	return (new3);
}


int main()
{
	// char str[] = "\"asd\"";
	char str[] = "<asd\"as<dasd\"<123> | asdsad fd's\"\"\"\"d'\"asd\"";
	printf("original:  %s\n", str);
	char *str2 = con(str);
	printf("new3: 	   %s\n", con(str));
	printf("should be: <\"asdas<dasd\"<\"123\"> | \"asdsad\" \"fds\"\"\"\"dasd\"\n");
	free (str2);
}
