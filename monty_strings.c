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


void pchar(stack_t **stack, unsigned int line_number)
{
	if (glob->size < 1)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	if ((!(65 <= (*stack)->n) || !((*stack)->n <= 90)) && (!(97 <= (*stack)->n) || !((*stack)->n <= 122)) )
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	putchar((*stack)->n);
	putchar('\n');
}

void pstr(stack_t **stack, __attribute__((unused))unsigned int line_number)
{
	stack_t *temp = NULL;

	if (glob->size < 1)
	{
		putchar('\n');
		return;
	}

	temp = *stack;
	while (temp)
	{
		if (1 <= temp->n && temp->n <= 127)
		{
			putchar(temp->n);
			temp = temp->next;
		}
		else
			break;
	}
	putchar('\n');
}
