#include "../../inc/minishell.h"
#include <sys/wait.h>


// if (is_builtin(cmd)) {
//     execute_builtin(cmd);
// } else {
//     pid_t pid = fork();
//     if (pid == 0) {
//         // Setup redirection
//         // Setup pipes
//         // Execute command
//         execve(...);
//     } else {
//         waitpid(pid, &status, 0);
//         update_exit_status(status);
//     }
// }


//execution{
// execute_ast
// wait()
//
//}

// int execute_ast(t_ast *node, t_minishell *shell)
// {
// 	if (!node)
// 		return (1);

// 	if (node->type == PIPE)
// 		return exec_pipe_node(node, shell);
// 	else
// 		return exec_command_node(node, shell);
// }

// int	exec_command_node(t_ast *cmd_node, t_minishell *mshell)
// {
// 	pid_t pid;
// 	int status;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("fork");
// 		return (1);
// 	}
// 	if (pid == 0)
// 	{
// 		//handle_redirections_from_ast(cmd_node);
// 		if (is_builtin(cmd_node->cmd[0]))
// 			exit(run_builtin(cmd_node->cmd, mshell));
// 		//exec_external(cmd_node->cmd, shell->envp);
// 		exit(127);
// 	}
// 	waitpid(pid, &status, 0);
// 	//pid = waitpid(0, &wstatus, 0);

// 	mshell->exitcode = WEXITSTATUS(status);
// 	return mshell->exitcode;
// }
//dup and dup2 back
// void traverse(t_ast *ast)
// {

// 	while (ast != NULL)
// 	{
// 		if (ast->type == PIPE)
// 			printf("%u", ast->type);
// 		while (ast != NULL)
// 		{
// 			// // redirection
// 			// exec_command_node(ast, shell);
// 			// //bui
// 			printf("%u", ast->type);
// 			ast = ast->next_left;
// 		}
// 		ast = ast->next_right;
// 	}
// }

// void traverse(t_ast *ast)
// {
//     // Pointer to traverse the main pipe chain (moves right)
//     t_ast *pipe_node = ast;
// 	t_ast *branch_node;

//     printf("Starting AST Traversal...\n");

//     // go thru the main chain (PIPE, linked via next_right)
//     while (pipe_node != NULL)
//     {
//         // PIPE
//         if (pipe_node->type == PIPE) {
//             printf(" (PIPE)\n");
//         } else if (pipe_node->type == COMMAND) {
//              printf(" (COMMAND: %s)\n", pipe_node->cmd ? pipe_node->cmd[0] : "N/A");
// 		}
// 		else if (pipe_node->type == 8) { //REDIRECT_OUT
//              printf(" (REDIRECT_OUT FILE: %s)\n", pipe_node->file ? pipe_node->file : "N/A");
//         } else {
//              printf(" (Type %d)\n", pipe_node->type);
//         }

//         if (pipe_node->next_left)
//         {
//             printf("  -> Traversing Left Branch:\n");
//             branch_node = pipe_node->next_left;

//             while (branch_node != NULL)
//             {
//                  printf("     Type: %d", branch_node->type);

//                  if (branch_node->type == COMMAND && branch_node->cmd && branch_node->cmd[0]) {
//                     printf(" (COMMAND: %s)\n", branch_node->cmd[0]);
//                  } else if (branch_node->file) {
//                     printf(" (FILE: %s)\n", branch_node->file);
//                  } else {
//                     printf(" (Type %d)\n", pipe_node->type);
//                  }
//                  branch_node = branch_node->next_left;
//             }
//             printf("  <- End of Left Branch\n");
//         } else {
//              printf("  -> No Left Branch\n");
//         }
//         printf(" -> Moving to right...\n");
//         pipe_node = pipe_node->next_right; // Only the main pointer moves right
//     }

//     printf("End.\n");
// }




void traverse(t_ast *ast)
{
    // Pointer to traverse the main pipe chain (moves right)
    t_ast *pipe_node = ast;
	t_ast *branch_node;

    printf("Starting AST Traversal...\n");

    // go thru the main chain (PIPE, linked via next_right)
    while (pipe_node != NULL)
    {
        // PIPE
        if (pipe_node->type == PIPE) {
           // execute_pipe();
			printf(" (PIPE)\n");

        // } else if (pipe_node->type == COMMAND) {
		// 	//execute_command();
        //     printf(" (COMMAND: %s)\n", pipe_node->cmd ? pipe_node->cmd[0] : "N/A");
		// }
		// else if (pipe_node->type == 8) { //I
		// 	//execute_redirection();
        //     printf(" (REDIRECT_OUT FILE: %s)\n", pipe_node->file ? pipe_node->file : "N/A");
        // } else {
        //      printf(" (Type %d)\n", pipe_node->type);
         }

        if (pipe_node->next_left)
        {
            printf("  -> Traversing Left Branch:\n");
            branch_node = pipe_node;

            while (branch_node != NULL)
            {
                 printf("     Type: %s\n", get_token_type_name(branch_node->type));

                 if (branch_node->type == COMMAND && branch_node->cmd && branch_node->cmd[0]) {
                    printf(" (COMMAND: %s)\n", branch_node->cmd[0]);
                 } else if (branch_node->file) {
                    printf(" (FILE: %s)\n", branch_node->file);
                 } else {
                    printf(" (Type %d)\n", pipe_node->type);
                 }
                 branch_node = branch_node->next_left;
            }
            printf("  <- End of Left Branch\n");
        } else {
             printf("  -> No Left Branch\n");
        }
        printf(" -> Moving to right...\n");
        pipe_node = pipe_node->next_right; // Only the main pointer moves right
    }

    printf("End.\n");
}
