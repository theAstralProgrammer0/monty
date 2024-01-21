#include "monty.h"

void insert_at_front(__attribute__((unused))stack_t **stack, int number)
{
	stack_t *newnode = NULL;

	newnode = (stack_t *) malloc(sizeof(stack_t));
	if (newnode == NULL)
		return;

	newnode->n = number;
	newnode->next = glob->front;
	newnode->prev = NULL;
	glob->front->prev = newnode;
	glob->front = newnode;
	
	glob->size++;
}

void insert_at_index(stack_t **stack, int number, unsigned int index)
{
	stack_t *newnode = NULL;
	stack_t *entry = NULL;
	unsigned int i;

	if (index > glob->size - 1)
		return;

	if (index == 0)
		insert_at_front(stack, number);

	else if (index == glob->size - 1)
		append(stack, number);
	else
	{
		newnode = (stack_t *) malloc(sizeof(stack_t));
		if (newnode == NULL)
			return;
		newnode->n = number;

		if (index >= glob->size - index - 1)
		{
			entry = glob->rear;
			for (i = 0; glob->size - index - 1; i++)
				entry = entry->prev;
			newnode->next = entry;
			newnode->prev = entry->prev;
			entry->prev->next = newnode;
		}
		else if (index < glob->size - index - 1)
		{
			entry = glob->front;
			for (i = 0; i < index; i++)
				entry = entry->next;
			newnode->next = entry;
			newnode->prev = NULL;
			glob->front->prev = newnode;
			glob->front = newnode;
		}
	}
	glob->size++;
}

void delete_node(stack_t *entry)
{
	if (entry == NULL)
		return;

	entry->next->prev = entry->prev;
	entry->prev->next = entry->next;
        entry->next = NULL;
        entry->prev = NULL;
        free(entry);
}
