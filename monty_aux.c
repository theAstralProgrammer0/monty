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
