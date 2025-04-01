#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_env
{
	char			**envp;                // array of strings: "KEY=VALUE"
	unsigned int	allocated_capacity;   // how many total entries allocated
	unsigned int	len;                   // how many are actually used
}	t_env;

int		copy_env(t_env **env, char **envp);
void free_env(t_env *env);
void free_partial_env(char **envp, int up_to);


#endif
