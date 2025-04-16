#include "../inc/minishell.h"

static int	arena_create_block(t_arena **arena)
{
	t_arenablock	*first;

	first = malloc(sizeof(t_arenablock) + INITIAL_SIZE);
	if (!first)
	{
		perror("malloc");
		return (FAIL);
	}
	first->next = NULL;
	first->capacity = INITIAL_SIZE;
	first->used = 0;
	(*arena)->first = first;
	(*arena)->current = first;
	return (SUCCESS);
}

static size_t	calc_actual_size(t_arena *a, size_t size, size_t alignment)
{
	// t_arenablock	*block;
	uintptr_t		ptr;
	uintptr_t		aligned;
	size_t			padding;
	size_t			actual_size;

	// block = a->current;
	ptr = (uintptr_t)a->current->data + a->current->used;
	aligned = (ptr + (alignment - 1)) & ~(alignment - 1);
	padding = aligned - ptr;
	actual_size = padding + size;
	return (actual_size);
}

void	*arena_alloc(t_arena *a, size_t size, size_t alignment)
{
	t_arenablock	*block;
	t_arenablock	*new_block;
	size_t			actual_size;
	size_t			new_size;
	void			*result;

	actual_size = calc_actual_size(a, size, alignment);
	block = a->current;
	// printf("capacity atm %li, used atm %li, needed %li\n", block->capacity, block->used, actual_size);
	if (block->used + actual_size > block->capacity)
	{
		new_size = a->default_block_size;

		while (new_size <= actual_size)
			new_size *= 2;
		new_block = malloc(sizeof(t_arenablock) + new_size);
		// printf("allocated block with size %li\n", new_size);
		if (!new_block)
			return(NULL);
		// printf("Arena allocation  %li\n", new_size);
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

void	init_arena_values(t_arena **arena)
{
	(*arena)->first = NULL;
	(*arena)->current = NULL;
	(*arena)->default_block_size = INITIAL_SIZE;
}

void	init_arena(t_minishell *mshell)
{
	mshell->arena = malloc(sizeof(t_arena));
	if (!mshell->arena)
		exit_cleanup_error(mshell, "malloc");
	init_arena_values(&mshell->arena);
	if (arena_create_block(&mshell->arena))
		exit_cleanup_error(mshell, "malloc");
}
