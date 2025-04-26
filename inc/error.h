/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:52:04 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 17:52:05 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

//error prompts
# define AC "Error: invalid number of arguments!\n"
# define BALANCE "Error: quotes or brackets unbalanced\n"
# define LINE_TOO_LONG "Error: input too long\n"
# define REDIR "Error: redirections invalid\n"
# define TOKEN_ERROR "syntax error near unexpected token"
# define UNREACHABLE "This is unreachable code, \
						something is wrong with error handling\n"
# define TMP_FILES "Too many heredoc redirections\n"
# define PIPE_ERROR " `|'"
# define INFILE_ERROR " `<'"
# define OUTFILE_ERROR " `>'"
# define APPENDFILE_ERROR " `>>'"
# define HEREDOC_ERROR " `<<'"
# define NEWLINE_ERROR " `newline'"
# define MALLOC "malloc fail"

//errors, exits and cleanups
void	delete_minishell(t_minishell *mshell);
void	exit_and_cleanup(t_minishell *mshell);
void	exit_error(t_minishell *mshell, char *msg);
void	exit_cleanup_error(t_minishell *mshell, char *msg);
void	print_error(char *msg, char *token, t_token_type type);

#endif
