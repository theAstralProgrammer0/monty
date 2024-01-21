#include "monty.h"

/**
 * push - opcode function
 *
 * Description: Adds an element to the top of the stack
 *
 * @stack: pointer to pointer to the top of the stack
 *
 * @line_number: line number in file
 *
 * Return: Nothing
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *newnode = NULL;
	int intNumber;

	if (glob->tokens[1] == NULL || !(isNumber(glob->tokens[1])))
	{
		free(glob->buffer);
		free_glob(glob);
		fprintf(stderr, "L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	intNumber = atoi(glob->tokens[1]);

	if (glob->mode == USE_QUEUE)
	{
		append(stack, intNumber);
		return;
	}

	newnode = (stack_t *)malloc(sizeof(stack_t));
	if (newnode == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}
	newnode->n = intNumber;
	newnode->next = *stack;
	newnode->prev = NULL;

	if (glob->size == 0)
	{
		glob->front = newnode;
		glob->rear = newnode;
	}
	else
		(*stack)->prev = newnode;
	*stack = newnode;
	glob->front = *stack;
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
	stack_t *temp = NULL;

	if (glob->mode == USE_STACK || glob->mode == DEFAULT_MODE)
		temp = *stack;
	if (glob->mode == USE_QUEUE)
		temp = glob->front;

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
	stack_t *temp = NULL;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	if (glob->mode == USE_STACK || glob->mode == DEFAULT_MODE)
		temp = *stack;
	if (glob->mode == USE_QUEUE)
		temp = glob->front;

	printf("%d\n", temp->n);
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
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}

	*stack = (*stack)->next;
	free(temp);
	glob->front = *stack;
	glob->size--;
}


/**
 * swap - opcode function
 *
 * Description: Swap elements on top of the stack
 *
 * @stack: pointer to pointer to the top of the stack
 * @line_number: line number in file
 *
 * Return: Nothing
 */
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
