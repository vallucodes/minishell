#include "../../inc/minishell.h"

static int check_ambiguous_redir(const char *file);

int	open_redir_file(const char *file, int flags, int *fd)
{
	if (check_ambiguous_redir(file) == FAIL)
	 	return (FAIL);
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	*fd = open(file, flags, 0644);
	if (*fd < 0)
	{
		ft_dprintf(2, "Giraffeshell: %s: %s\n", file, strerror(errno), errno);
		return (FAIL);
	}
	return (SUCCESS);
}

static int check_ambiguous_redir(const char *file)
{
	int i;

	i = 0;
	if (!file || *file == '\0')
	{
		ft_dprintf(2, "Giraffeshell: %s: ambiguous redirect\n", file);  // TODO 
		return (FAIL);
	}
	// while (file[i])
	// {
	// 	if (file && file[i] !='\0')
	// 	{
	// 		ft_dprintf(2, "Giraffeshell: %s: ambiguous redirect\n", file);
	// 		return (FAIL);
	// 	}
	// 	else
	// 	{
	// 		ft_dprintf(2, "Giraffeshell: : ambiguous redirect\n");
	// 	}
	// 	i++;
	// }
	return (SUCCESS);
}
