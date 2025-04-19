#include "../../inc/minishell.h"

static char	*build_cmd_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (temp == NULL)
		return (NULL);// TODO
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

char	*get_cmd_full_path(char **path, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path && path[i])
	{
		full_path = build_cmd_path(path[i], cmd);
		if (!full_path)
			return (NULL);// TODO
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_command_path(t_minishell *mshell, t_ast *ast)
{
	char	*full_path;

	if (!ast->cmd)
		return (NULL);// TODO

	full_path = NULL;

	if (!ft_strchr(ast->cmd[0], '/'))
	{
		full_path = get_cmd_full_path(mshell->path, ast->cmd[0]);

		if (!full_path)
		{
			ft_dprintf(2, "Giraffeshell: %s: command not found\n", ast->cmd[0]);
			exit(127);
		}
	}
	else
	{
		full_path = ft_strdup(ast->cmd[0]);
		if(!full_path)
			return (NULL);// TODO
	}
	return (full_path);
}

