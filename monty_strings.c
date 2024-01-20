#include "monty.h"
#include "errno.h"

/**
 * isNumber - Aux function
 *
 * Description: Checks if a string is an actual number
 *
 * @digitstr: Digit string
 *
 * Return: 1 Success, O Failure
 */
int isNumber(const char *digitstr)
{
	char *endptr;

	if (digitstr == NULL)
		return (0);

	strtol(digitstr, &endptr, 10);
	if (endptr == digitstr)
		return (0);

	if (*endptr != '\0')
		return (0);

	if (errno == ERANGE)
		return (0);

	return (1);
}

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
	temp->n -= (*stack)->n;
	temp->prev = NULL;
	free(*stack);
	*stack = temp;
	glob->size--;
}
