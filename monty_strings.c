#include "monty.h"
#include "errno.h"

/**
 * isNumber - Aux function
 *
 * Description: Checks if a string is an actual number
 *
 * @digitstr: Digit string
 *
 * Return: 1 Success, O Failure
 */
int isNumber(const char *digitstr)
{
	char *endptr;

	if (digitstr == NULL)
		return (0);

	strtol(digitstr, &endptr, 10);
	if (endptr == digitstr)
		return (0);

	if (*endptr != '\0')
		return (0);

	if (errno == ERANGE)
		return (0);

	return (1);
}
