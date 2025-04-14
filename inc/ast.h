#ifndef AST_H
# define AST_H
typedef struct s_ast
{
	t_token_type	type;
	char			**cmd;
	char			*file;
	struct s_ast	*next_left;
	struct s_ast	*next_right;
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

//ast
t_ast	*build_ast_binary_tree(t_arena **arena, t_token *tokens);
void	build_branch(t_arena **arena, t_ast **ast, t_token *tokens, t_branch branch);
void	add_node(t_ast **ast, t_ast *new_node, t_order order);
t_ast	*init_node(t_arena **arena, char **cmd, char *file, t_token_type type);

//ast utils
int		count_amount_cmd(t_token *tokens);
size_t	get_amount_of_pipes(t_token *tokens);
int		last_is_pipe(t_ast **ast);
t_token	*skip_to_next_pipe(t_token *tokens);

#endif
