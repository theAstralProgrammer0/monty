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
	newnode->next = *stack;
	newnode->prev = NULL;

	if (*stack)
		(*stack)->prev = newnode;
	*stack = newnode;
	glob->size++;
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
void pall(stack_t **stack, __attribute__((unused))unsigned int line_number)
{
	stack_t *temp = *stack;

	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

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
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		fclose(glob->fp);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

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
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
		fclose(glob->fp);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	*stack = (*stack)->prev;
	free(temp);
	glob->size--;
}
