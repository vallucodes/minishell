#include <strings.h>
#include <stdio.h>
#include "../inc/minishell.h"

void	next_temp_file(char *file, int nb)
{
	char	*char_nb;
	int		i;
	int		j;

	file[0] = 't';
	file[1] = 'm';
	file[2] = 'p';
	char_nb = ft_itoa(nb);
	// if (!char_nb)
		// exit_error(MALLOC);
	i = 3;
	j = 0;
	while (char_nb[j])
	{
		file[i] = char_nb[j];
		i++;
		j++;
	}
	file[i] = '\0';
	free(char_nb);
}


int	create_tmp_file()
{
	int		fd;
	char	file[256];
	int		index;

	index = 1;
	while (1)
	{
		ft_bzero(file, 256);
		next_temp_file(file, index);
		if (access (file, F_OK) != 0)
			break ;
		index++;
		// if (index > 1000)
			// exit_error(TOO MANY TEMP FILES)
	}
	fd = open(file, O_WRONLY | O_CREAT | O_EXCL, 0644);
	// if (fd < 0)
		// exit_error(TMP_FILE_CREATION_FAILED);
	return (fd);
}

int main(int ac, char **av)
{
	printf("fd %i\n", create_tmp_file());
	return 0;
}
