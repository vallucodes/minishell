#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"

//expansion
size_t	expand_pid(t_minishell *mshell, int fd, char **new_str);
size_t	expand_content(t_minishell *mshell, char *str, int fd, char **new_str);
size_t	expand_exitcode_value(t_minishell *mshell, int fd, char **new_str);
void	write_or_add_to_str(t_minishell *mshell, int fd, char **new_str,
			char *str_pid);
size_t	skip_to_start_of_expandable(char *env_row);
size_t	get_len_explandeble(char *str);

#endif
