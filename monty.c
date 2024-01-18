#include "monty.h"

glob_t *glob = NULL;

/**
 * stack_init - Aux function
 *
 * Description: Initializes the stack and returns the top/head of the stack
 *
 * Return: Nothing
 */
void stack_init(void)
{
	stack_t *top = NULL;
	stack_t **stack = &top;
	size_t inst_num, i;

	glob = malloc(sizeof(glob_t));
	if (glob == NULL)
	{
		dprintf(2, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	glob->top = top;
	glob->stack = stack;
	glob->fp = NULL;
	glob->buffer = NULL;
	
	glob->tokens = malloc(2 * sizeof(char *));
	if (glob->tokens == NULL)
	{
		free_glob(glob);
		dprintf(2, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * execop - Aux function
 *
 * Description: This executes the monty operation based on the opcode passed as
 * token
 *
 * @line_number: line number of the instruction
 *
 * Return: Nothing
 */
void execop(unsigned int line_number)
{
	int i, num;
	char *opcode = NULL;

	opcode = glob->tokens[0];
	printf("opcode (glob->tokens[0]): %s\n", opcode);

	if (opcode == NULL)
		return;
	instruction_t insts[2] = {
		{"push", push},
		{"pall", pall}
	};

	num = sizeof(insts) / sizeof(insts[0]);

	for (i = 0; i < num; i++)
	{
		if (strcmp(opcode, insts[i].opcode) == 0)
		{
			insts[i].f(glob->stack, line_number);
			return;
		}
	}
	dprintf(2, "L%u: unknown instruction %s\n", line_number, opcode);
	fclose(glob->fp);
	free(glob->buffer);
	free_glob(glob);
	exit(EXIT_FAILURE);
}

/**
 * tokenizer - Aux function
 *
 * Description: Tokenizes the line from monty file passed as an argument. It
 * also keeps track of how many tokens are in each line
 *
 * @line: String contained in a line of instruction
 * @delim: Delimeter string
 *
 * Return: Nothing
 */
void tokenizer(char *line, const char *delim)
{
	int i, token_count = 0;
	char *token = strtok(line, delim);

	while (token != NULL && token_count < 2)
	{
		glob->tokens[token_count] = token;
		token_count++;

		token = strtok(NULL, delim);
	}

	for (i = token_count; i < MAX_TOKENS; i++)
		glob->tokens[i] = NULL;	
}


int main(int argc, char **argv)
{
	char *buffer = NULL, *buffer_copy = NULL;
	size_t size = 0;
	unsigned int line_number = 1;

	if (argc != 2)
	{
		dprintf(2, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	stack_init();
	glob->fp = fopen(argv[1], "r");
	if (glob->fp == NULL)
	{
		if(glob)
			free_glob(glob);
		dprintf(2, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}


	while (getline(&buffer, &size, glob->fp) != -1)
	{
		glob->buffer = buffer;

		tokenizer(buffer, " \t\n");
		execop(line_number);

		line_number++;
	}
	free(buffer);
	free(glob->buffer);
	fclose(glob->fp);
	free_glob(glob);
	return (0);
}
