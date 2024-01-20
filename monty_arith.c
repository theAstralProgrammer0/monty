#include "monty.h"

void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (glob->size < 2)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	(*stack)->next = temp->next;
	(*stack)->prev = temp;
	temp->next = (*stack);
	temp->prev = NULL;
	(*stack) = temp;
}

void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (glob->size < 2)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	temp->n += (*stack)->n;
	temp->prev = NULL;
	free(*stack);
	*stack = temp;
}
