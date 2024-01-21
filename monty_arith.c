#include "monty.h"

/**
 * add - Aux function
 *
 * Description: Adds first two values of a data structure (stack or queue)
 *
 * @stack: Double pointer to the data strucure (stack or queue)
 *
 * @line_number: Line Number in monty file
 *
 * Return: Nothing
 */

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
	glob->front = *stack;
	glob->size--;
}


/**
 * sub - Aux function
 *
 * Description: Subtracts first two values of a data structure (stack or queue)
 *
 * @stack: Double pointer to the data strucure (stack or queue)
 *
 * @line_number: Line Number in monty file
 *
 * Return: Nothing
 */
void sub(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (glob->size < 2)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	temp->n -= (*stack)->n;
	temp->prev = NULL;
	free(*stack);
	*stack = temp;
	glob->front = *stack;
	glob->size--;
}


/**
 * mul - Aux function
 *
 * Description: Multiplies first two values of data structure (stack or queue)
 *
 * @stack: Double pointer to the data strucure (stack or queue)
 *
 * @line_number: Line Number in monty file
 *
 * Return: Nothing
 */

void mul(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (glob->size < 2)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	temp->n *= (*stack)->n;
	temp->prev = NULL;
	free(*stack);
	*stack = temp;
	glob->front = *stack;
	glob->size--;
}

/**
 * custom_div - Aux function
 *
 * Description: Divides first two values of a data structure (stack or queue)
 *
 * @stack: Double pointer to the data strucure (stack or queue)
 *
 * @line_number: Line Number in monty file
 *
 * Return: Nothing
 */
void custom_div(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (glob->size < 2)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	temp->n /= (*stack)->n;
	temp->prev = NULL;
	free(*stack);
	*stack = temp;
	glob->front = *stack;
	glob->size--;
}

/**
 * mod - Aux function
 *
 * Description: Finds remainder from division of the first two values of a data
 * structure (stack or queue)
 *
 * @stack: Double pointer to the data strucure (stack or queue)
 *
 * @line_number: Line Number in monty file
 *
 * Return: Nothing
 */
void mod(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (glob->size < 2)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	temp = (*stack)->next;
	temp->n %= (*stack)->n;
	temp->prev = NULL;
	free(*stack);
	*stack = temp;
	glob->front = *stack;
	glob->size--;
}
