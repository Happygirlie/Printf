#include "main.h"

/**
 * print_pointer - This program prints a pointer
 * @types: The arguments used
 * @buffer: Buffer array for the print
 * @flags: This calculates active flags
 * @width: The width
 * @precision: The precision
 * @size: The size
 * Return: The number of characters printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long no_address;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	no_address = (unsigned long)addrs;

	while (no_address > 0)
	{
		buffer[ind--] = map_to[no_address % 16];
		no_address /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/**
 * print_non_printable - This is a program that prints non printable characters
 * @types: The arguments used
 * @buffer: Buffer array for the print
 * @flags: Gets the active flags
 * @width: The width
 * @precision:The precision
 * @size: The size
 * Return: The number of characters printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, ofset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + ofset] = str[i];
		else
			ofset += append_hexa_code(str[i], buffer, i + ofset);

		i++;
	}

	buffer[i + ofset] = '\0';

	return (write(1, buffer, i + ofset));
}

/**
 * print_reverse - This program prints the reverse of a string
 * @types: The arguments used
 * @buffer: Buffer array for the print
 * @flags: This gets the active flags
 * @width: The width
 * @precision: The precision
 * @size: The size
 * Return: Number of characters printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, figure = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		figure++;
	}
	return (figure);
}

/**
 * print_rot13string - A program that prints a rot13string
 * @types: The arguments used
 * @buffer: Buffer array for the print
 * @flags: Gets the active flags
 * @width: The width
 * @precision: The precision
 * @size: The size
 * Return: Number of characters printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int fig = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				fig++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			fig++;
		}
	}
	return (fig);
}
