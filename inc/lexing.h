typedef enum e_quotes
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quotes;

typedef enum e_token_type
{
	WORD,				// some word in quotes or without quotes
	COMMAND,			// word classified as command
	ARG,				// word classified as argument to command
	FILE_TOKEN,			// word classified as file
	HERE_TOKEN,			// word classified as heredoc
	PIPE,				// |
	REDIRECT_IN,		// <
	REDIRECT_OUT,		// >
	REDIRECT_APPEND,	// >>
	HERE_STRING,		// <<
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
