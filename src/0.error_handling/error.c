#include "../inc/minishell.h"

// void	exit error()
// {

// } to-do

void	print_error(char *msg, char *token, t_token_type type)
{
	if (token)
		printf("%s%s\n", msg, token);
	if (type)
	{
		if (type == REDIRECT_IN)
			ft_dprintf(2, "%s%s\n", msg, INFILE_ERROR);
		else if (type == REDIRECT_OUT)
			ft_dprintf(2, "%s%s\n", msg, OUTFILE_ERROR);
		else if (type == REDIRECT_APPEND)
			ft_dprintf(2, "%s%s\n", msg, APPENDFILE_ERROR);
		else if (type == HERE_DOCUMENT)
			ft_dprintf(2, "%s%s\n", msg, HEREDOC_ERROR);
		else if (type == PIPE)
			ft_dprintf(2, "%s%s\n", msg, PIPE_ERROR);
		else
			ft_dprintf(2, UNREACHABLE);
	}
}



