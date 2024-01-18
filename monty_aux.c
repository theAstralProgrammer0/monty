#include "monty.h"

/**
 * free_glob - Aux function
 *
 * Description: Frees the global struct
 *
 * @glob: pointer to the global struct
 *
 * Return: Nothing
 */

void free_glob(glob_t *glob)
{
	int i;
	stack_t *current = NULL, *next = NULL;

	if (glob == NULL)
		return;

	if (glob->tokens)
		free(glob->tokens);

	if (glob->stack && glob->top)
		current = glob->top;

	while (current)
	{
		if (current->next)
		{
			next = current->next;
			free(current);
			current = next;
		}
		else
		{
			free(current);
			break;
		}
	}
	free(glob);
}
