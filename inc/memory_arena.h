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
