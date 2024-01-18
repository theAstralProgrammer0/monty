#include "monty.h"

/**
 * push - opcode function
 *
 * Description: Adds an element to the top of the stack
 *
 * @stack: pointer to pointer to the top of the stack
 * @line_number: line number in file
 *
 * Return: Nothing
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *newnode = NULL;
	int intNumber;

	if (glob == NULL)
		return;
	if (!(glob->tokens[1]))
		return;
	if (!isNumber(glob->tokens[1]))
	{
		fclose(glob->fp);
		free(glob->buffer);
		free_glob(glob);
		dprintf(2, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	intNumber = atoi(glob->tokens[1]);

	newnode = (stack_t *)malloc(sizeof(stack_t));
	if (newnode == NULL)
	{
		dprintf(2, "Error: malloc failed\n");
		fclose(glob->fp);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}
	newnode->n = intNumber;
	newnode->next = glob->top;
	newnode->prev = NULL;

	if (glob->top)
		glob->top->prev = newnode;
	glob->top = newnode;
}


/**
 * pall - opcode function
 *
 * Description: Prints the elements of the stack
 *
 * @stack: pointer to pointer to the top of the stack
 * @line_number: line number in file
 *
 * Return: Nothing
 */
void pall(stack_t **stack, unsigned int line_number)
{
	printf("HI\n");
}
