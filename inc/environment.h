#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_env
{
	char			**envp;                // array of strings: "KEY=VALUE"
	unsigned int	allocated_capacity;   // how many total entries allocated
	unsigned int	len;                   // how many are actually used
}	t_env;

#endif