typedef struct s_ast
{
	t_token_type	type;
	char			**cmd;
	char			*file;
	struct s_ast	*next_left;
	struct s_ast	*next_right;
	// struct s_ast	*previous;
}	t_ast;

typedef enum e_order
{
	FIRST,
	NON_FIRST,
}	t_order;

typedef enum e_branch
{
	LAST_BRANCH,
	NON_LAST_BRANCH,
}	t_branch;

