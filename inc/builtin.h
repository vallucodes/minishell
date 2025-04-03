
#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>

typedef struct s_env t_env;
typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;


int		is_valid_identifier_range(const char *str, size_t len);

int		match_env_key(const char *env_entry, const char *key);

int		count_cmds(char **cmds);
int		execute_builtins(t_minishell *mshell, t_ast *ast);
int		realloc_env_capacity(t_env *env);
char	**dup_and_sort_env(t_env *env);


int		ft_env(t_env **my_env, char **args);
int		ft_pwd(void);
int		ft_echo(int argc, char **argv);
void	ft_exit(char **args, t_minishell *minishell);
int		ft_unset(char **args, t_env *env);
int		ft_export(char **args, t_env *env);

#endif
