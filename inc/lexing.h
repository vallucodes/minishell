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
	WORD = 1,			// some word in quotes or without quotes
	COMMAND,			// word classified as command
	ARG,				// word classified as argument to command
	FILE_TOKEN,			// word classified as file
	HERE_TOKEN,			// word classified as heredoc
	PIPE,				// |
	REDIRECT_IN,		// <
	REDIRECT_OUT,		// >
	REDIRECT_APPEND,	// >>
	HERE_DOCUMENT,		// <<
	ENV_VAR,			// $
}	t_token_type;

typedef struct s_token
{
	char			*value;
	int				len;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct	s_input
{
	char	*full_str;	// The full user input
	int		index;		// track position while scanning
	int		len;		// len helps check if end of input is reached
	t_token	*tokens;
}				t_input;

typedef struct s_quotes_helper
{
	int	in_double;
	int	in_single;
	int	in_quotes;
	int	previous_in_quotes;
}				t_quotes_helper;

typedef struct s_minishell t_minishell;

//tokenizer
void	init_lexer(t_input *new_input, char *input_str);
void	create_tokens(t_minishell *mshell, t_input *input);
int		tokenizer(t_minishell *mshell, t_input *input, char *input_str);
int		tokens_validation(t_token *tokens);
void	retokenize_words(t_token *tokens);

//tokenizer utils
int		is_separator(char c);
int		is_quote(char c);
int		is_operator(char c);
int		is_valid_char(t_quotes_helper *quotes, t_input *input);
void	update_quote_state(char c, t_quotes_helper *quotes);

#endif
