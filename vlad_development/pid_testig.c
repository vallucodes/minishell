# include <stdlib.h> //NULL
# include <unistd.h> //execve, fork
# include <fcntl.h> //pid_t
# include <stdio.h> //perror
# include <sys/wait.h> //wait

int main()
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		exit (0);
	printf("%i", pid);
	return (0);
}
