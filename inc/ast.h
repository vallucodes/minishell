typedef struct s_ast
{
	t_token_type	type;
	char			**cmd;
	char			*file;
	struct s_ast	*next_left;
	struct s_ast	*next_right;
	struct s_ast	*previous;
}	t_ast;


// typedef struct s_token
// {
// 	char			*value;
// 	int				len;
// 	t_token_type	type;
// 	struct s_token	*next;
// }				t_token;
