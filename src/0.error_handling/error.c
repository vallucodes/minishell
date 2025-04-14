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
			printf("%s%s\n", msg, INFILE_ERROR);
		else if (type == REDIRECT_OUT)
			printf("%s%s\n", msg, OUTFILE_ERROR);
		else if (type == REDIRECT_APPEND)
			printf("%s%s\n", msg, APPENDFILE_ERROR);
		else if (type == HERE_DOCUMENT)
			printf("%s%s\n", msg, HEREDOC_ERROR);
		else if (type == PIPE)
			printf("%s%s\n", msg, PIPE_ERROR);
		else
			printf(UNREACHABLE);
	}
}



