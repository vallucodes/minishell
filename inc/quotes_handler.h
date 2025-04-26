/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:51:51 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 17:51:52 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_HANDLER_H
# define QUOTES_HANDLER_H

# include "minishell.h"

//quote handler
void	expand_remove_quotes(t_minishell *mshell, t_input *input);
void	init_vars(t_minishell *mshell, t_vars *vars, t_token *current);
int		handle_expandables(t_minishell *mshell,
			t_vars *vars, size_t *i, t_token *current);
bool	is_ambiguous_redirect(t_minishell *mshell,
			t_quotes_helper quotes, t_token *current, char *str);

//quote utils
bool	is_valid_expandable(t_quotes_helper quotes, char *input_str);
bool	is_any_word(t_token_type type);
bool	expandable_exists(int len, char **env, size_t i, char *str);
bool	is_exitcode_expansion(t_quotes_helper quotes, char *input_str);
bool	is_pid_expansion(t_quotes_helper quotes, char *input_str);
bool	is_exp_is_empty_is_bare_is_cmd_or_arg(t_vars vars, t_token *curr);

void	update_vars_quote(t_vars *vars, size_t *i);
void	update_vars_append(t_minishell *mshell, t_vars *vars, size_t *i);
bool	process_expandable(size_t i, t_token *current, char	**env);

#endif
