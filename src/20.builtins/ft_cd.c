#include "../../inc/minishell.h"
#include <linux/limits.h>

static int	check_env_updates(t_env *env, const char *old_pwd);
static int	update_pwd(t_env *env);
static int	update_oldpwd(t_env *env, const char *old_pwd);
static int	go_home(t_env *my_env);

int	ft_cd(t_env **my_env, int argv_count, char **argv)
{
	char old_pwd[PATH_MAX];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
	{
		perror("getcwd");
		return (FAIL);
	}
	if (argv_count == 1)
	{
		if (go_home(*my_env) == FAIL)
			return (FAIL);
	}
	else if (argv_count > 2)
	{
		ft_dprintf(STDERR_FILENO, "Giraffeshell: cd: too many arguments\n");
		return (FAIL);
	}
	else if (chdir(argv[1]) != 0)
	{
		ft_dprintf(STDERR_FILENO, "Giraffeshell: cd: %s: %s\n", argv[1], strerror(errno));
		return (FAIL);
	}
	if (check_env_updates(*my_env, old_pwd))
		return (FAIL);
	return (SUCCESS);
}

static int	check_env_updates(t_env *env, const char *old_pwd)
{
	int failed = 0;

	if (update_oldpwd(env, old_pwd))
		failed = 1;
	if (update_pwd(env))
		failed = 1;

	if (failed)
		return (1);
	return (0);
}

static int	update_pwd(t_env *env)
{
	char cwd[PATH_MAX];
	char *full_path_var;

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);

	full_path_var = ft_strjoin("PWD=", cwd);
	if (!full_path_var)
	{
		ft_dprintf(2, "Giraffeshell: cd: malloc failed\n");
		return (1);
	}
	if (!update_var_env(env, full_path_var, "PWD", 1)
		&& !add_var_to_env(env, full_path_var, "PWD", 3, 1))
	{
		ft_dprintf(2, "Giraffeshell: cd: malloc failed\n");
		free(full_path_var);
		return (1);
	}
	free(full_path_var);
	return (0);
}

static int	update_oldpwd(t_env *env, const char *old_pwd)
{
	char *full_path_var;

	full_path_var = ft_strjoin("OLDPWD=", old_pwd);
	if (!full_path_var)
	{
		ft_dprintf(2, "Giraffeshell: cd: malloc failed\n");
		return (1);
	}
		if (!update_var_env(env, full_path_var, "OLDPWD", 1)
		&& !add_var_to_env(env, full_path_var, "OLDPWD", 6, 1))
	{
		ft_dprintf(2, "Giraffeshell: cd: malloc failed\n");
		free(full_path_var);
		return (1);
	}
	free(full_path_var);
	return (0);
}

static int	go_home(t_env *my_env)
{
	char *home;

	home = get_env_value(my_env->envp, "HOME");
	if (!home)
	{
		ft_dprintf(STDERR_FILENO, "Giraffeshell: cd: HOME not set\n");
		return (FAIL);
	}
	if (chdir(home) != 0)
	{
		ft_dprintf(STDERR_FILENO, "Giraffeshell: cd: %s: %s\n", home, strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}
