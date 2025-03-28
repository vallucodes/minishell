#include <strings.h>
#include <stdio.h>
#include "../inc/minishell.h"

size_t	expand_content(char **env, char *str, int fd)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = 0;
	while (str[len] && !ft_isspace(str[len]))
		len++;
	i = 0;
	while(env[i])
	{
		if (ft_strncmp(&env[i][0], &str[1], len - 1) == 0)
		{
			j = 0;
			while (env[i][j])
			{
				while (env[i][j] != '=')
					j++;
				while (env[i][j])
					write(fd, &env[i][j++], 1);
			}
		}
		i++;
	}
	return (len);
}

void	save_to_file(char **env, char *input, int fd, t_expand expand)
{
	size_t	i;

	i = 0;
	if (expand == DONT_EXPAND)
	{
		while (input[i])
			write(fd, &input[i++], 1);
		write(fd, "\n", 1);
	}
	else
	{
		while (input[i])
		{
			if (input[i] == '$' && !ft_isspace(input[i + 1]))
				i += expand_content(env, &input[i], fd);
			write(fd, &input[i++], 1);
		}
		write(fd, "\n", 1);
	}
}

void	read_line(char **env, char *eof, t_expand expand)
{
	char	*input;
	int		fd;

	fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	input = readline(">");
	while (ft_strncmp(eof, input, ft_strlen(eof)) || (ft_strlen(input) != ft_strlen(eof)))
	{
		save_to_file(env, input, fd, expand);
		free(input);
		input = NULL;
		input = readline(">");
	}
	free(input);
	input = NULL;
	// save to file
}

#include <stdlib.h>
#include <string.h>

char **fill_env()
{
    extern char **environ;
    char **env = NULL;
    int env_count = 0;

    // Count the number of environment variables
    while (environ[env_count] != NULL)
        env_count++;

    // Allocate memory for the new environment array
    env = malloc((env_count + 1) * sizeof(char *));
    if (env == NULL)
        return NULL;

    // Copy environment variables
    for (int i = 0; i < env_count; i++)
    {
        env[i] = strdup(environ[i]);
        if (env[i] == NULL)
        {
            // Free previously allocated memory if strdup fails
            for (int j = 0; j < i; j++)
                free(env[j]);
            free(env);
            return NULL;
        }
    }

    // Null-terminate the array
    env[env_count] = NULL;

    return env;
}

void	print_env(char **env)
{
	int i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
}

int main(int ac, char **av)
{
	char **env;

	env = fill_env();
	// print_env(env);
	if (ac == 2)
		read_line(env, av[1], EXPAND);
	return 0;
}
