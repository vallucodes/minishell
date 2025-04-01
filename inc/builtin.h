
#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>

typedef struct s_env t_env;
typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;

int execute_builtins(t_minishell *mshell, t_ast *ast);
int ft_env(t_env **my_env, char **args);
int ft_pwd(void);
int	ft_echo(int argc, char **argv);
int ft_exit(t_minishell *mshell);

//int ft_cd(t_env *env, char **args);
//int execute_builtin(t_minishell *mshell, t_ast_test *ast);

#endif
