#include "main.h"
int handle_numbers(shellinfo_t *ourtype, char *argument)
{
	int tracer;

	tracer = _atoi(argument);

	if (tracer < 0 || has_letter(argument))
	{
		ourtype->code_stat = 2;
		ourtype->error_digit = 133;
		additional_error(ourtype, argument);
		return (0);
	}

	if (tracer > 255)
	{
		ourtype->code_stat = tracer % 256;
	}
	else
	{
		ourtype->code_stat = tracer;
	}

	return (1);
}
