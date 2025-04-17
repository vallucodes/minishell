#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_env
{
	char			**envp;                // array of strings: "KEY=VALUE"
	unsigned int	allocated_capacity;   // how many total entries allocated
	unsigned int	len;                   // how many are actually used

}	t_env;

//main
int		copy_env(t_env **env, char **envp);
int		match_env_key(const char *env_entry, const char *key);
char	*get_env_value(char **envp, const char *key);
int		realloc_env_capacity(t_env *env);
char	**dup_and_sort_env(t_env *env);

//exits
void	free_env(t_env *env);
void	exit_env(char *msg, t_env **env);
void	free_partial_env(char **envp, int up_to);

#endif
