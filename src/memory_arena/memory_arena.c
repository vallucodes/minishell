#include "../inc/minishell.h"

t_arena	arena_create(size_t initial_size)
{
	t_arena			arena;
	t_arenablock	*first;

	first =  malloc(sizeof(t_arenablock) + initial_size);
	// if (!first)
	// 	exit_error(MALLOC);
	first->next = NULL;
	first->capacity = initial_size;
	first->used = 0;
	arena.first = first;
	arena.current = first;
	arena.default_block_size = initial_size;
	return (arena);
}

static size_t	calc_actual_size(t_arena *a, size_t size, size_t alignment)
{
	t_arenablock *block = a->current;
	uintptr_t ptr = (uintptr_t)block->data + block->used;

	// Debugging output
	// printf("\n--- calc_actual_size ---\n");
	// printf("block->data address: %p\n", block->data);
	// printf("block->used: %zu\n", block->used);
	// printf("ptr (block->data + used): %p\n", (void *)ptr);
	// printf("alignment: %zu\n", alignment);

	uintptr_t aligned = (ptr + (alignment - 1)) & ~(alignment - 1);
	size_t padding = aligned - ptr;
	size_t actual_size = padding + size;

	// More debugging output
	// printf("aligned address: %p\n", (void *)aligned);
	// printf("padding: %zu\n", padding);
	// printf("actual_size: %zu\n", actual_size);

	return actual_size;
}

void	*arena_alloc(t_arena *a, size_t size, size_t alignment)
{
	t_arenablock	*block;
	t_arenablock	*new_block;
	size_t			actual_size;
	size_t			new_size;
	void			*result;

	actual_size = calc_actual_size(a, size, alignment);
	printf("actual size needed %li\n", actual_size);
	block = a->current;
	if (block->used + actual_size > block->capacity)
	{
		new_size = a->default_block_size;

		while (new_size <= actual_size)
		{
			new_size *= 2;
			// printf("new size iteration %li\n", new_size);
		}
		new_block = malloc(sizeof(t_arenablock) + new_size);
		// printf("allocated block with size %li\n", new_size);
		// if (!new_block)
		// 	exit_error(MALLOC);
		new_block->next = NULL;
		new_block->capacity = new_size;
		new_block->used = 0;

		a->current->next = new_block;
		a->current = new_block;
		block = new_block;
	}
	result = block->data + block->used;
	block->used += actual_size;
	return (result);
}

void	arena_destroy(t_arena *a)
{
	t_arenablock *block;
	t_arenablock *next;

	block = a->first;
	while (block)
	{
		next = block->next;
		free(block);
		block = next;
	}
	a->first = a->current = NULL;
}
