#include "main.h"
/**
 * my_hndle_prnt - This program prints an argument based on its type
 * @frmt: This is the formatted string to print the arguments to
 * @list: The list of arguments to be printed.
 * @i: The integer used
 * @buffer: The buffer array used
 * @flags: Should calculates active flags
 * @width:The width
 * @precision: The precision
 * @size: The size
 * Return: 1 or 2 if successful
 */
int my_hndle_prnt(const char *frmt, int *i, va_list list, char buffer[],
	int flags, int width, int precision, int size)
{
	int a, unknwn_len = 0, prntd_chars = -1;
	frmt_t frmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (a = 0; frmt_types[a].frmt != '\0'; a++)
		if (frmt[*i] == frmt_types[a].frmt)
			return (frmt_types[a].fn(list, buffer, flags, width, precision, size));

	if (frmt_types[a].frmt == '\0')
	{
		if (frmt[*i] == '\0')
			return (-1);
		unknwn_len += write(1, "%%", 1);
		if (frmt[*i - 1] == ' ')
			unknwn_len += write(1, " ", 1);
		else if (width)
		{
			--(*i);
			while (frmt[*i] != ' ' && frmt[*i] != '%')
				--(*i);
			if (frmt[*i] == ' ')
				--(*i);
			return (1);
		}
		unknwn_len += write(1, &frmt[*i], 1);
		return (unknwn_len);
	}
	return (prntd_chars);
}
