/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:37:18 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/26 17:54:37 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_minishell	mshell;
	t_ast		*ast;
	t_input		input;

	if (ac != 1)
		exit_error(NULL, AC);
	if (init_minishell(&mshell, envp, &ast, av) != 0)
		exit_error(&mshell, "Error: Failed to initialize minishell\n");
	run_minishell(&mshell, &input, &ast);
	delete_minishell(&mshell);
	return (0);
}
