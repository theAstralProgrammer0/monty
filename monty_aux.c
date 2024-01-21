#include "monty.h"

void append(stack_t **stack, int number)
{
        stack_t *newnode = NULL;

        if (*stack == NULL)
                return;
        
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

void pop_at_index(stack_t **stack, unsigned int line_number, unsigned int index)
{
	stack_t *temp = NULL;
	stack_t *entry = NULL;
	unsigned int i;

	if (index > glob->size - 1)
		return;

	if (index == 0)
		pop(stack, line_number);

	if (index == glob->size - 1)
	{
		temp = glob->rear;
		temp->prev->next = NULL;
		glob->rear = temp->prev;
		temp->prev = NULL;
		free(temp);
	}
	else
	{
		if (index >= glob->size - index - 1)
		{
			entry = glob->rear;
			for (i = 0; i < glob->size - index - 1; i++)
				entry = entry->prev;
			delete_node(entry);
		}
		else if (index < glob->size - index - 1)
		{
			entry = glob->front;
			for (i = 0; i < index; i++)
				entry = entry->next;
			delete_node(entry);
		}
	}
	glob->size--;
}


void rotl(stack_t **stack, unsigned int line_number)
{
	int num;

	if (glob->size < 2)
		return;
	
	num = glob->front->n;
	pop(stack, line_number);
	append(stack, num);
}

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
