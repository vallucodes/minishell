#include "../inc/minishell.h"

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
		case HERE_DOCUMENT: return "HERE_STRING";
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

void	print_whole_arena(t_arena *a)
{
    t_arenablock *block = a->first;

    printf("==== Arena Contents ====\n");
    while (block != NULL)
	{
        printf("Block at %p (used: %zu bytes, capacity: %zu bytes):\n",
               (void *)block, block->used, block->capacity);

        // Print raw bytes
        for (size_t i = 0; i < block->used; i++)
		{
            if (i % 16 == 0)
				printf("\n%04zx: ", i); // New line every 16 bytes
            printf("%02x ", block->data[i]);
        }
        printf("\n\n");

        block = block->next;
    }
    printf("========================\n");
}
