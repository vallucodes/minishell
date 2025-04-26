/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:13:24 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/26 15:13:27 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

typedef enum e_quotes
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quotes;

typedef enum e_token_type
{
	WORD = 1,
	COMMAND,
	ARG,
	FILE_TOKEN,
	HERE_TOKEN,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HERE_DOC,
	ENV_VAR,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	int				len;
	t_token_type	type;
	bool			ambiguous;
	struct s_token	*next;
}				t_token;

typedef struct s_input
{
	char	*full_str;
	int		index;
	int		len;
	t_token	*tokens;
}				t_input;

typedef struct s_quotes_helper
{
	int	in_double;
	int	in_single;
	int	in_quotes;
	int	previous_in_quotes;
}				t_quotes_helper;

typedef struct s_vars
{
	t_quotes_helper	quotes;
	char			*new_str;
	char			*input_str;
	size_t			i;
	bool			is_bare_exp;
}				t_vars;

typedef struct s_minishell	t_minishell;

//tokenizer
void	init_lexer(t_input *new_input, char *input_str);
void	create_tokens(t_minishell *mshell, t_input *input);
int		tokenizer(t_minishell *mshell, t_input *input);
int		tokens_validation(t_minishell *mshell, t_token *tokens);
void	retokenize_words(t_token *tokens);

//tokenizer utils
int		is_separator(char c);
int		is_quote(char c);
int		is_operator(char c);
int		is_valid_char(t_quotes_helper *quotes, t_input *input);
void	update_quote_state(char c, t_quotes_helper *quotes);
t_token	*skip_until_pipe_or_end(t_token *current);

#endif
