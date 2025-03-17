typedef enum e_quotes
{
	NONE,
	SINGLE,
	DOUBLE,
}	t_quotes;

typedef enum e_token_type
{
	WORD_DOUBLE,		// some word in double quotes "Something here"
	WORD_SINGLE,		// some word in single quotes 'Something here'
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
