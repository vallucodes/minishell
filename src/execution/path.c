#include "../../inc/minishell.h"
# include "../lib/libft/inc/libft.h"

static char	*build_cmd_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (temp == NULL)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

static int	join_cmd_path(char **cmd_argv, char **path, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path && path[i])
	{
		full_path = build_cmd_path(path[i], cmd);
		if (!full_path)
			return (0);
		if (access(full_path, X_OK) == 0)
		{
			free(cmd_argv[0]);
			cmd_argv[0] = full_path;
			return (1);
		}
		free(full_path);
		i++;
	}
	return (0);
}

static char	**allocate_cmd_argv(char *cmd)
{
	char	**cmd_argv;

	cmd_argv = ft_split(cmd, ' ');
	if (!cmd_argv)
		return (NULL);
	if (!cmd_argv[0])
	{
		ft_free_2d(cmd_argv);
		cmd_argv = malloc(sizeof(char *) * 2);
		if (!cmd_argv)
			return (NULL);
		cmd_argv[0] = ft_strdup(cmd);
		cmd_argv[1] = NULL;
	}
	return (cmd_argv);
}

char	**get_command_argv(t_minishell *mshell, t_ast *ast)
{
	char	**cmd_argv;

	if (!ast->cmd)
		return (NULL);
	cmd_argv = allocate_cmd_argv(*ast->cmd);
	if (!cmd_argv)
		return (NULL);
	if (!ft_strchr(cmd_argv[0], '/'))
	{
		if (!join_cmd_path(cmd_argv, mshell->path, cmd_argv[0]))
		{
			ft_dprintf(2, "Giraffeshell: %s: command not found\n", cmd_argv[0]);
			ft_free_2d(cmd_argv);
			exit(127);
		}
	}
	return (cmd_argv);
}

