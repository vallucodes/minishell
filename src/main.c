#include "../inc/minishell.h"

//For testing purpose

char *get_token_type_name(t_token_type token_type)
{
	switch (token_type)
	{
		case WORD: return "WORD";
		case COMMAND: return "COMMAND";
		case ARG: return "ARG";
		case FILE_TOKEN: return "FILE";
		case HERE_TOKEN: return "HERE_WORD";
		case PIPE: return "PIPE";
		case REDIRECT_IN: return "REDIRECT_IN";
		case REDIRECT_OUT: return "REDIRECT_OUT";
		case REDIRECT_APPEND: return "REDIRECT_APPEND";
		case HERE_STRING: return "HERE_STRING";
		case ENV_VAR: return "ENV_VAR";
		default: return "UNKNOWN";
	}
}

void print_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->value)
		{
			printf("Type: %15s, Length of token: %d, Value: %.*s\n", get_token_type_name(tokens->type), tokens->len, tokens->len, tokens->value);
		}
		tokens = tokens->next;
	}
	printf("\n");
}

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

typedef struct ArenaBlock {
    struct ArenaBlock *next;
    size_t capacity;
    size_t used;
    uint8_t data[];
} ArenaBlock;

typedef struct {
    ArenaBlock *first;
    ArenaBlock *current;
    size_t default_block_size;
} Arena;

// Initialize arena with default block size
Arena arena_create(size_t initial_size) {
    ArenaBlock *first = malloc(sizeof(ArenaBlock) + initial_size);
    first->next = NULL;
    first->capacity = initial_size;
    first->used = 0;

    return (Arena){
        .first = first,
        .current = first,
        .default_block_size = initial_size
    };
}

// Allocate memory from arena (automatically grows)
void *arena_alloc(Arena *a, size_t size, size_t alignment) {
    ArenaBlock *block = a->current;

    // Calculate aligned offset
    uintptr_t ptr = (uintptr_t)block->data + block->used;
    uintptr_t aligned = (ptr + (alignment - 1)) & ~(alignment - 1);
    size_t actual_size = (aligned - ptr) + size;

    // Allocate new block if needed (exponential growth)
    if (block->used + actual_size > block->capacity) {
        size_t new_size = a->default_block_size;
        while (new_size < size) new_size *= 2;

        ArenaBlock *new_block = malloc(sizeof(ArenaBlock) + new_size);
        new_block->next = NULL;
        new_block->capacity = new_size;
        new_block->used = 0;

        a->current->next = new_block;
        a->current = new_block;
        a->default_block_size *= 2;  // Exponential growth
        block = new_block;
    }

    void *result = block->data + block->used;
    block->used += actual_size;
    return result;
}

// Free all arena blocks
void arena_destroy(Arena *a) {
    ArenaBlock *block = a->first;
    while (block) {
        ArenaBlock *next = block->next;
        free(block);
        block = next;
    }
    a->first = a->current = NULL;
}

//Testing ends

int main(int ac, char **av, char **envp)
{
	char		*input_str;
	t_input		input;
	t_ast		*ast;
	t_minishell	mshell;

	(void) av;

	if (ac != 1)
		return (FAIL);
		// exit_error(AC ERROR)
	if (init_minishell(&mshell, envp))
		return (FAIL);
		// exit_error(init_issue)
	while (1)
	{
		input_str = readline(PROMPT);
		if (!input_str)
			break ;
		add_history(input_str);
		if (!input_validation(input_str))
		{
			// expand(input_str);//double quote or single quote expasion
			init_lexer(&input, input_str);
			extract_token(&input);
			if (tokens_validation(input.tokens) == SUCCESS)
			{
				retokenize_words(input.tokens);
				handle_heredoc(mshell.envp->envp, input.tokens);
				print_tokens(input.tokens);
				ast = build_ast_binary_tree(input.tokens);
				free(input_str); // dont free this before the whole program ends!
			}
		}
	}
	//free_env(&mshell.env); // must free environment here after loop end
	return (0);
}

// ls -la < file1 > file1.1| cat -e >file2 <<file3 | grep filename >>file4 | du -s > file5
