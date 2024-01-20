#include "monty.h"

void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (stack || glob->size < 2)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	(*stack)->next = temp->next;
	(*stack)->prev = temp;
	temp->next->prev = (*stack);
	temp->prev = NULL;
	temp->next = (*stack);
	(*stack) = temp;
}
