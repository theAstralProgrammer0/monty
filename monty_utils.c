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
#pragma GCC diagnostic ignored "-Wunused-parameter"
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *newnode = NULL;
	int intNumber;

	if (glob == NULL)
		return;
	if (glob->tokens[1] == NULL || !(isNumber(glob->tokens[1])))
	{
		fclose(glob->fp);
		free(glob->buffer);
		free_glob(glob);
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	intNumber = atoi(glob->tokens[1]);

	newnode = (stack_t *)malloc(sizeof(stack_t));
	if (newnode == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
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
#pragma GCC diagnostic pop

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
#pragma GCC diagnostic ignored "-Wunused-parameter"
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = glob->top;

	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}
#pragma GCC diagnostic pop

/**
 * pint - opcode function
 *
 * Description: Prints the element on top of the stack
 *
 * @stack: pointer to pointer to the top of the stack
 * @line_number: line number in file
 *
 * Return: Nothing
 */
#pragma GCC diagnostic ignored "-Wunused-parameter"
void pint(stack_t **stack, unsigned int line_number)
{
	if (glob->top == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		fclose(glob->fp);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", glob->top->n);
}
#pragma GCC diagnostic pop

/**
 * pop - opcode function
 *
 * Description: Deletes the element on top of the stack
 *
 * @stack: pointer to pointer to the top of the stack
 * @line_number: line number in file
 *
 * Return: Nothing
 */
#pragma GCC diagnostic ignored "-Wunused-parameter"
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = glob->top;

	if (glob->top == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		fclose(glob->fp);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	glob->top = glob->top->prev;
	free(temp);
}
#pragma GCC diagnostic pop
