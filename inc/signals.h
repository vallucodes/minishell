/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:51:49 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 18:19:21 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern volatile sig_atomic_t	g_signal;
typedef struct s_minishell		t_minishell;

void	sigint_handler_main(int signal);
void	sigint_handler_heredoc(int signal);
void	sigint_handler_parent(int signal);

bool	sig_action_ignore(t_minishell *mshell);
bool	sig_action_main(t_minishell *mshell);
bool	sig_action_heredoc(t_minishell *mshell);
bool	sig_action_parent(t_minishell *mshell);
bool	sig_action_default(t_minishell *mshell);

void	set_exitcode_signal(t_minishell *mshell);

#endif
