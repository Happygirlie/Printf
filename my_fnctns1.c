#include "main.h"

/**
 * print_unsigned - The program prints an unsigned number
 * @types: The arguments used
 * @buffer: Buffer array for the print
 * @flags:  Should calculate active flags
 * @width: The width
 * @precision: The precision
 * @size: The size
 * Return: Number of characters printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int no = va_arg(types, unsigned long int);

	no = convert_size_unsgnd(no, size);

	if (no == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (no > 0)
	{
		buffer[i--] = (no % 10) + '0';
		no /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: The arguments
 * @buffer: Buffer array for the print
 * @flags:  Gets the active flags
 * @width: The width
 * @precision: The precision
 * @size: The size
 * Return: The number of characters printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int no = va_arg(types, unsigned long int);
	unsigned long int init_no = no;

	UNUSED(width);

	no = convert_size_unsgnd(no, size);

	if (no == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (no > 0)
	{
		buffer[i--] = (no % 8) + '0';
		no /= 8;
	}

	if (flags & F_HASH && init_no != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: The arguments used
 * @buffer: An array of buffer for the print
 * @flags: The flags that are active
 * @width: The width
 * @precision: The precision
 * @size: The size
 * Return: The number of characters printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lists the arguments
 * @buffer: Buffer array to handle the print
 * @flags: Gets active flags
 * @width: The width
 * @precision: The precision
 * @size: The size
 * Return: The number of characters printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper case
 * @types: The arguments used
 * @map_to: Array of values to map to
 * @buffer: Buffer array for the print
 * @flags: Gets active flags
 * @flag_ch: The active flags
 * @width: The width
 * @precision: The precision
 * @size: Size specifier
 * @size: The size
 * Return: Number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int no = va_arg(types, unsigned long int);
	unsigned long int init_no = no;

	UNUSED(width);

	no = convert_size_unsgnd(no, size);

	if (no == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (no > 0)
	{
		buffer[i--] = map_to[no % 16];
		no /= 16;
	}

	if (flags & F_HASH && init_no != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
