// #include <strings.h>
#include <stdio.h>
// #include <stdalign.h>
// #include "../inc/minishell.h"

// typedef struct	t_mystruct
// {
// 	struct	t_arenablock *next;
// 	size_t	capacity;
// 	size_t	used;
// 	uint8_t	data[];
// }	t_mystruct;

// int main()
// {
// 	t_mystruct b;

// 	printf("size is %lu, alingment is %lu\n", sizeof(b), alignof(t_mystruct));
// 	return 0;
// }


#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>

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

t_arena arena_create(size_t initial_size)
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

size_t calc_actual_size(t_arena *a, size_t size, size_t alignment) {
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


//usage
#include <stdio.h>
#include <stdlib.h>
#include <stdalign.h>

int main()
{
    // Step 1: Create an arena with an initial block size of 1024 bytes
    t_arena arena = arena_create(1024);
    printf("Arena created with initial block size: %zu bytes\n", arena.default_block_size);

    // Step 2: Allocate memory for integers
    int *nums = arena_alloc(&arena, sizeof(int) * 10, alignof(int));
    if (!nums) {
        fprintf(stderr, "Failed to allocate memory for integers\n");
        return EXIT_FAILURE;
    }
    printf("Allocated memory for 10 integers\n");

    // Fill the allocated memory with values
    for (int i = 0; i < 10; i++) {
        nums[i] = i * i; // Store square values
    }

    // Print the stored values
    printf("Stored values in allocated integer array:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    // Step 3: Allocate memory for a string
    char *str = arena_alloc(&arena, 50, alignof(char));
    if (!str) {
        fprintf(stderr, "Failed to allocate memory for string\n");
        return EXIT_FAILURE;
    }
    printf("Allocated memory for a string of length 50\n");

    // Store a string in the allocated memory
    snprintf(str, 50, "Hello, Arena Allocator!");
    printf("Stored string: %s\n", str);

    // Step 4: Allocate memory for floating-point numbers
    float *floats = arena_alloc(&arena, sizeof(float) * 20, alignof(float));
    if (!floats) {
        fprintf(stderr, "Failed to allocate memory for floats\n");
        return EXIT_FAILURE;
    }
    printf("Allocated memory for 20 floats\n");

    // Fill the allocated memory with values
    for (int i = 0; i < 20; i++) {
        floats[i] = (float)i / 2.0f; // Store half values
    }

    // Print the stored values
    printf("Stored values in allocated float array:\n");
    for (int i = 0; i < 20; i++) {
        printf("%.2f ", floats[i]);
    }
    printf("\n");

    // Step 5: Test dynamic growth of the arena
    size_t large_size = arena.default_block_size * 2;
    void *large_alloc = arena_alloc(&arena, large_size, 16);
    if (!large_alloc) {
        fprintf(stderr, "Failed to allocate large block of size %zu\n", large_size);
        return EXIT_FAILURE;
    }
    printf("Successfully allocated a large block of size %zu bytes\n", large_size);

	// Step 7: Test dynamic growth of the arena very large
	size_t large_size2 = 6854;
	void *large_alloc2 = arena_alloc(&arena, large_size2, 17);
	if (!large_alloc)
	{
        fprintf(stderr, "Failed to allocate large block of size %zu\n", large_size2);
        return EXIT_FAILURE;
	}
	printf("Successfully allocated a large block of size %zu bytes\n", large_size2);

    // Step 99: Destroy the arena and free all blocks
    arena_destroy(&arena);
    printf("Arena destroyed and all blocks freed\n");

    return EXIT_SUCCESS;
}
