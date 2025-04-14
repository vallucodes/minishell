#ifndef MEMORY_ARENA_H
# define MEMORY_ARENA_H

# define INITIAL_SIZE 512
typedef struct	t_arenablock
{
	struct	t_arenablock *next;
	size_t	capacity;
	size_t	used;
	uint8_t	data[];
}	t_arenablock;

typedef struct t_arena
{
	t_arenablock	*first;
	t_arenablock	*current;
	size_t			default_block_size;
}	t_arena;

t_arena	arena_create();
void	*arena_alloc(t_arena *a, size_t size, size_t alignment);
void	arena_destroy(t_arena **a);
void	init_arena(t_arena **arena);

#endif
