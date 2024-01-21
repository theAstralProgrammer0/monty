#include "monty.h"

/**
 * append - Aux Function
 *
 * Description: This function adds a new node to the rear of the list
 *
 * @stack: Double pointer to the data structure (stack or queue)
 *
 * @number: n member of the stack_t node type
 *
 * Return: Nothing.
 */

void append(__attribute__((unused))stack_t **stack, int number)
{
	stack_t *newnode = NULL;

	newnode = (stack_t *)malloc(sizeof(stack_t));
	if (newnode == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		free(glob->buffer);
		free_glob(glob);
		exit(EXIT_FAILURE);
	}
	newnode->n = number;
	newnode->next = NULL;
	newnode->prev = glob->rear;

	if (glob->size == 0)
	{
		glob->front = newnode;
		glob->rear = newnode;
	}
	else
	{
		glob->rear->next = newnode;
	}
	glob->rear = newnode;
	glob->size++;
}

/**
 * pop_at_index - Aux Function
 *
 * Description: This function deletes a node at an index of the list
 *
 * @stack: Double pointer to the data structure (stack or queue)
 *
 * @line_number: line number in monty file
 *
 * @idx: index
 *
 * Return: Nothing.
 */
void pop_at_index(stack_t **stack, unsigned int line_number, unsigned int idx)
{
	stack_t *temp = NULL;
	stack_t *entry = NULL;
	unsigned int i;

	if (idx > glob->size - 1)
		return;

	if (idx == 0)
		pop(stack, line_number);

	if (idx == glob->size - 1)
	{
		temp = glob->rear;
		temp->prev->next = NULL;
		glob->rear = temp->prev;
		temp->prev = NULL;
		free(temp);
	}
	else
	{
		if (idx >= glob->size - idx - 1)
		{
			entry = glob->rear;
			for (i = 0; i < glob->size - idx - 1; i++)
				entry = entry->prev;
			delete_node(entry);
		}
		else if (idx < glob->size - idx - 1)
		{
			entry = glob->front;
			for (i = 0; i < idx; i++)
				entry = entry->next;
			delete_node(entry);
		}
	}
	glob->size--;
}


/**
 * rotl - Aux Function
 *
 * Description: This function rotates the data structure left
 *
 * @stack: Double pointer to the data structure (stack or queue)
 *
 * @line_number: line number in monty file
 *
 * Return: Nothing.
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	int num;

	if (glob->size < 2)
		return;

	num = glob->front->n;
	pop(stack, line_number);
	append(stack, num);
}

/**
 * rotr - Aux Function
 *
 * Description: This function rotates the data structure right
 *
 * @stack: Double pointer to the data structure (stack or queue)
 *
 * @line_number: line number in monty file
 *
 * Return: Nothing.
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	int num;

	if (glob->size < 2)
		return;

	num = glob->rear->n;
	pop_at_index(stack, line_number, glob->size - 1);
	insert_at_index(stack, num, 0);
}

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
	stack_t *current = NULL, *next = NULL;

	if (glob == NULL)
		return;

	if (glob->tokens)
		free(glob->tokens);

	if (glob->stack && *(glob->stack))
		current = *(glob->stack);

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
	if (glob->fp)
		fclose(glob->fp);
	free(glob);
}
