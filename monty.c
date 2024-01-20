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
	/* allocate memory for the global structure */
	glob = malloc(sizeof(glob_t));
	if (glob == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	/* initialize global structure members */
	glob->stack = &(glob->front);
	glob->front = NULL;
	glob->rear = NULL;
	glob->fp = NULL;
	glob->buffer = NULL;
	glob->tokens = malloc(2 * sizeof(char *));
	if (glob->tokens == NULL)
	{
		free_glob(glob);
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	glob->size = 0;
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
	instruction_t insts[INSTRUCTIONS] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop}
	};
	int i, num;
	char *opcode = NULL;

	opcode = glob->tokens[0];

	if (opcode == NULL)
		return;

	num = sizeof(insts) / sizeof(insts[0]);

	for (i = 0; i < num; i++)
	{
		if (strcmp(opcode, insts[i].opcode) == 0)
		{
			insts[i].f(glob->stack, line_number);
			return;
		}
	}
	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
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

/**
 * main - Entry Point
 *
 * Description: Calls all functions for performing monty operations on the
 * stack
 *
 * @argc: Argument count
 * @argv: Strings array from terminal
 *
 * Return: 0 Success, Otherwise Failure
 */
int main(int argc, char **argv)
{
	char *buffer = NULL;
	size_t size = 0;
	unsigned int line_number = 1;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	stack_init();
	glob->fp = fopen(argv[1], "r");
	if (glob->fp == NULL)
	{
		if (glob)
			free_glob(glob);
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (getline(&buffer, &size, glob->fp) != -1)
	{
		glob->buffer = buffer;

		tokenizer(buffer, " \t\n");
		execop(line_number);

		line_number++;
	}
	free(glob->buffer);
	free_glob(glob);
	return (0);
}
