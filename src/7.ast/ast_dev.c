#include "../inc/minishell.h"

#define CMD_FIELD_WIDTH 30

void print_cmd(char **cmd)
{
    if (cmd == NULL || cmd[0] == NULL)
    {
        printf("%-*s", CMD_FIELD_WIDTH, "Cmd: NULL");
    }
    else
    {
        char cmd_str[CMD_FIELD_WIDTH + 1] = "Cmd: ";
        int i = 0;
        int len = 5; // "Cmd: " is already 5 characters

        while (cmd[i] && len < CMD_FIELD_WIDTH)
        {
            size_t remaining = CMD_FIELD_WIDTH - len;
            int to_copy = (strlen(cmd[i]) < remaining) ? strlen(cmd[i]) : remaining - 1;
            strncat(cmd_str, cmd[i], to_copy);
            strcat(cmd_str, " ");
            len += to_copy + 1;
            i++;
        }
        printf("%-*s", CMD_FIELD_WIDTH, cmd_str);
    }
}

void print_node(t_ast *node)
{
    printf("Type: %15s ", get_token_type_name(node->type));
    print_cmd(node->cmd);
    printf("file: %20s ", node->file ? node->file : "NULL");
    printf("ambiguous: %s\n", node->ambiguous ? "true" : "false");
}

void print_left_side(t_ast *ast)
{
    t_ast *tmp = ast->next_left;
	printf("left\n");
    while (tmp)
    {
        print_node(tmp);
        tmp = tmp->next_left;
		printf("left\n");
    }
}

void print_whole_tree(t_ast *ast)
{
    while (ast)
    {
        print_node(ast);
        if (ast->next_left)
        {
            print_left_side(ast);
        }
        ast = ast->next_right;
		printf("right\n");
    }
}
