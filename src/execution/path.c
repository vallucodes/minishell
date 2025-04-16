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
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL); // not found in any path
}


// static int	join_cmd_path(char **cmd_argv, char **path, char *cmd)
// {
// 	int		i;
// 	char	*full_path;

// 	i = 0;
// 	while (path && path[i])
// 	{
// 		full_path = build_cmd_path(path[i], cmd);
// 		if (!full_path)
// 			return (0);
// 		if (access(full_path, X_OK) == 0)
// 		{
// 			free(cmd_argv[0]);
// 			cmd_argv[0] = full_path;
// 			return (1);
// 		}
// 		free(full_path);
// 		i++;
// 	}
// 	return (0);
// }

// static char	**allocate_cmd_argv(char *cmd)
// {
// 	char	**cmd_argv;

// 	cmd_argv = ft_split(cmd, ' ');
// 	if (!cmd_argv)
// 		return (NULL);
// 	if (!cmd_argv[0])
// 	{
// 		ft_free_2d(cmd_argv);
// 		cmd_argv = malloc(sizeof(char *) * 2);
// 		if (!cmd_argv)
// 			return (NULL);
// 		cmd_argv[0] = ft_strdup(cmd);
// 		cmd_argv[1] = NULL;
// 	}
// 	return (cmd_argv);
// }

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

