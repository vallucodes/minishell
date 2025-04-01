
#ifndef BUILTINS_H
# define BUILTINS_H



# include <stdio.h>

typedef struct s_env t_env;
typedef struct s_ast t_ast;
typedef struct s_minishell t_minishell;

typedef struct s_ast_test {
	char			**cmd;         // command and args
}	t_ast_test;

int ft_env(t_env *env, char **args);
//int ft_cd(t_env *env, char **args);
int execute_builtin(t_minishell *mshell, t_ast_test *ast);

#endif
