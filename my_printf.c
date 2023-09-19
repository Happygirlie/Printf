#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Pogram for a printf function
 * @frmt: format
 * Return: Printed characters
 */
int _printf(const char *frmt, ...)
{
	int i, prntd = 0, prntd_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (frmt == NULL)
		return (-1);

	va_start(list, frmt);

	for (i = 0; frmt && frmt[i] != '\0'; i++)
	{
		if (frmt[i] != '%')
		{
			buffer[buff_ind++] = frmt[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &frmt[i], 1);*/
			prntd_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_my_flags(frmt, &i);
			width = get_width(frmt, &i, list);
			precision = get_precision(frmt, &i, list);
			size = gets_my_size(frmt, &i);
			++i;
			prntd = my_hndle_prnt(frmt, &i, list, buffer,
				flags, width, precision, size);
			if (prntd == -1)
				return (-1);
			prntd_chars += prntd;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (prntd_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
