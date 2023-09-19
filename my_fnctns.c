#include "main.h"

/**
 * print_char - This program prints a character
 * @types: Types of arguments
 * @buffer: Buffer array for the print
 * @flags:  This calculates the active flags
 * @width: The width
 * @precision: The precision
 * @size: The size
 * Return: Number of characters printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char f = va_arg(types, int);

	return (handle_write_char(f, buffer, flags, width, precision, size));
}

/**
 * print_string - A program that prints a string
 * @types: The types of arguments
 * @buffer: Buffer array for the print
 * @flags: Should calculate active flags
 * @width: The width.
 * @precision: The precision
 * @size: The size
 * Return: Number of characters printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *string = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (string == NULL)
	{
		string = "(null)";
		if (precision >= 6)
			string = "      ";
	}

	while (string[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &string[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &string[0], length);
			return (width);
		}
	}

	return (write(1, string, length));
}

/**
 * print_percent - A program that prints a percent sign
 * @types: Types of arguments used
 * @buffer: Buffer array to handle the print
 * @flags:  This should calculate active flags
 * @width: This gets the width
 * @precision: The precision 
 * @size: The size
 * Return: Number of characters printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}


/**
 * print_int - A program used to print int
 * @types: This lists the types of arguments
 * @buffer: An array of buffer to handle print
 * @flags:  This gets the active flags
 * @width: The width
 * @precision: The precision
 * @size: The size
 * Return: Number of characters printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int m = va_arg(types, long int);
	unsigned long int numb;

	m = convert_size_number(m, size);

	if (m == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	numb = (unsigned long int)m;

	if (m < 0)
	{
		numb = (unsigned long int)((-1) * m);
		is_negative = 1;
	}

	while (numb > 0)
	{
		buffer[i--] = (numb % 10) + '0';
		numb /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/**
 * print_binary - This program prints a binary
 * @types: The arguments
 * @buffer: Buffer array for the print
 * @flags:  Should calculate the active flags
 * @width: Gets the width
 * @precision: The precision
 * @size: The size
 * Return: Number of characters printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int c, d, j, sum;
	unsigned int b[32];
	int counting;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	c = va_arg(types, unsigned int);
	d = 2147483648; /* (2 ^ 31) */
	b[0] = c / d;
	for (j = 1; j < 32; j++)
	{
		d /= 2;
		b[j] = (c / d) % 2;
	}
	for (j = 0, sum = 0, counting = 0; j < 32; j++)
	{
		sum += b[j];
		if (sum || j == 31)
		{
			char z = '0' + b[j];

			write(1, &z, 1);
			counting++;
		}
	}
	return (counting);
}
