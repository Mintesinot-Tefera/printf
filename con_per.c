#include "main.h"

unsigned int conv_c(va_list arg, buf_er * output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_percent(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_p(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);

/**
 * conv_c - Converts an argument to an unsigned char and
 *             stores it to a in a struct.
 * @arg: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_c(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char c;
	unsigned int r = 0;

	(void)precision;
	(void)len;

	c = va_arg(arg, int);

	r += pr_width(output, r, flags, width);
	r += mem_cpy(output, &c, 1);
	r += pr_neg_width(output, r, flags, width);

	return (r);
}

/**
 * conv_percent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @arg: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int conv_percent(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char percent = '%';
	unsigned int r = 0;

	(void)arg;
	(void)precision;
	(void)len;

	r += pr_width(output, r, flags, width);
	r += mem_cpy(output, &percent, 1);
	r += pr_neg_width(output, r, flags, width);

	return (r);
}

/**
 * conv_p - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @arg: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_p(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char *null = "(nil)";
	unsigned long int address;
	unsigned int r = 0;

	(void)len;

	address = va_arg(arg, unsigned long int);
	if (address == '\0')
		return (mem_cpy(output, null, 5));

	flags |= 32;
	r += conv_ubase(output, address, "0123456789abcdef",
			flags, width, precision);
	r += pr_neg_width(output, r, flags, width);

	return (r);
}
