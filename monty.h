#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

#define MAX_TOKENS 2

#define USE_STACK 2
#define USE_QUEUE 1
#define DEFAULT_MODE 0

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct global_var - global struct and its members
 * 
 * @stack: pointer to the top pointer of the stack
 * @top: pointer to the top node of the stack
 * @front: pointer to front of the queue
 * @rear: pointer to rear of the queue
 * @tokens: string array containing tokens
 *
 * Description: global struct containing all features of the stack (or queues)
 */
typedef struct global_var
{
	stack_t **stack;
	stack_t *top;
	stack_t *front;
	stack_t *rear;
	char **tokens;
	FILE *fp;
	char *buffer;
	size_t size;
	int mode;
} glob_t;

/* external global variable declared */
extern glob_t *glob;

#define SET_MODE_STACK() (glob->mode = USE_STACK)
#define SET_MODE_QUEUE() (glob->mode = USE_QUEUE)
#define SET_MODE_DEFAULT() (glob->mode = DEFAULT_MODE)

/* stack operation functions */
void push(stack_t **stack, unsigned int line_number);
void pall(stack_t **stack, unsigned int line_number);
void pint(stack_t **stack, unsigned int line_number);
void pop(stack_t **stack, unsigned int line_number);
void swap(stack_t **stack, unsigned int line_number);
void add(stack_t **stack, unsigned int line_number);
void sub(stack_t **stack, unsigned int line_number);
void mul(stack_t **stack, unsigned int line_number);
void custom_div(stack_t **stack, unsigned int line_number);
void mod(stack_t **stack, unsigned int line_number);
void pchar(stack_t **stack, unsigned int line_number);
void pstr(stack_t **stack, unsigned int line_number);
void rotl(stack_t **stack, unsigned int line_number);
void rotr(stack_t **stack, unsigned int line_number);
void insert_at_front(__attribute__((unused))stack_t **stack, int number);
void insert_at_index(stack_t **stack, int number, unsigned int index);
void delete_node(stack_t *entry);
void append(stack_t **stack, int number);
void pop_at_index(stack_t **stack, unsigned int line_number, unsigned int index);

/* stack utility functions */
void stack_init(void);
void execop(unsigned int line_number);
void tokenizer(char *line, const char *delim);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

/* other function prototypes */
void free_glob(glob_t *glob);
int isNumber(const char *digitstr);

#endif
