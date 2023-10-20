#include "main.h"

unsigned int conv_x(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_X(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);

/**
 * conv_x - Converts an unsigned int argument to hexa using abcdef
 *             and stores it to a buffer contained in a struct.
 * @arg: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A bufer struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_x(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	unsigned long int num;
	unsigned int r = 0;
	char *lead = "0x";

	if (len == LONG)
		num = va_arg(arg, unsigned long int);
	else
		num = va_arg(arg, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		r += mem_cpy(output, lead, 2);

	if (!(num == 0 && precision == 0))
		r += conv_ubase(output, num, "0123456789abcdef",
				flags, width, precision);

	r += pr_neg_width(output, r, flags, width);

	return (r);
}

/**
 * conv_X - Converts an unsigned int argument to hex using ABCDEF
 *             and stores it to a buffer contained in a struct.
 * @arg: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buf_er struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_X(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	unsigned long int num;
	unsigned int r = 0;
	char *lead = "0X";

	if (len == LONG)
		num = va_arg(arg, unsigned long);
	else
		num = va_arg(arg, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		r += mem_cpy(output, lead, 2);

	if (!(num == 0 && precision == 0))
		r += conv_ubase(output, num, "0123456789ABCDEF",
				flags, width, precision);

	r += pr_neg_width(output, r, flags, width);

	return (r);
}
