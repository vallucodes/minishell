#ifndef AST_H
# define AST_H
typedef struct s_ast
{
	t_token_type	type;
	char			**cmd;
	char			*file;
	bool			ambiguous; //add this in ast creation
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

typedef struct s_ast_vars
{
	t_token_type	type;
	char			**cmd;
	char			*file;
	bool			ambiguous;
}	t_ast_vars;

//ast
void	build_ast_binary_tree(t_minishell *mshell, t_token *tokens, t_ast **ast);
void	build_branch(t_minishell *mshell, t_ast **ast, t_token *tokens, t_branch branch);
void	add_node(t_ast **ast, t_ast *new_node, t_order order);
t_ast	*init_node(t_minishell *mshell, char **cmd, t_token *tokens, t_token_type type);

//ast utils
int		count_amount_cmd(t_token *tokens);
size_t	get_amount_of_pipes(t_token *tokens);
int		last_is_pipe(t_ast **ast);
t_token	*skip_to_next_pipe(t_token *tokens);

#endif
