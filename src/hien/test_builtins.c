#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../../inc/builtin.h"

typedef struct s_env {
	char			**envp;
	unsigned int	allocated_capacity;
	unsigned int	len;
}	t_env;

typedef struct s_minishell {
	t_env	envp;
	int		exitcode;
}	t_minishell;

// typedef struct s_ast_test {
// 	char			**cmd;         // command and args
// }	t_ast_test;

// Declare external builtins
int ft_env(t_env *env, char **args);
int execute_builtin(t_minishell *mshell, t_ast_test *ast);

// -------------------- ENV HELPERS --------------------

void free_env(t_env *env)
{
	unsigned int i = 0;

	if (!env || !env->envp)
		return;

	while (i < env->len)
		free(env->envp[i++]);
	free(env->envp);
	env->envp = NULL;
	env->len = 0;
	env->allocated_capacity = 0;
}

void free_partial_env(char **envp, int up_to)
{
	while (up_to--)
		free(envp[up_to]);
	free(envp);
}

static int init_env_storage(t_env *env, char **envp)
{
	int	var_amount = 0;

	while (envp[var_amount])
		var_amount++;
	env->envp = malloc(sizeof(char *) * (var_amount + 1));
	if (!env->envp)
	{
		ft_dprintf(2, "malloc error\n");
		return (1);
	}
	env->allocated_capacity = var_amount + 1;
	env->len = 0;
	return (0);
}

int copy_env(t_env *env, char **envp)
{
	int	i;

	if (init_env_storage(env, envp))
		return (1);

	i = 0;
	while (envp[i])
	{
		env->envp[i] = strdup(envp[i]);
		if (!env->envp[i])
		{
			ft_dprintf(2, "malloc error\n");
			free_partial_env(env->envp, i);
			return (1);
		}
		i++;
	}
	env->envp[i] = NULL;
	env->len = i;
	return (0);
}

// -------------------- MAIN TEST --------------------


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_minishell mshell = {0};

	t_ast_test ast = {.cmd = 0};

	// Set up environment
	if (copy_env(&mshell.envp, envp) != 0)
	{
		ft_dprintf(2, "Failed to copy environment\n");
		return (1);
	}

	// Set up AST command to simulate: `env`
	char *cmd[] = { "env", "gg", "gdgdg",  NULL };
	ast.cmd = cmd;
	printf("DEBUG: ast->cmd[0] in main = \"%s\"\n", ast.cmd[0]);

	// Run builtin
	mshell.exitcode = execute_builtin(&mshell, &ast);
	printf("\nBuiltin exittttt code: %d\n", mshell.exitcode);

	free_env(&mshell.envp);
	return 0;
}
