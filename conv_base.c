#include "main.h"

unsigned int conv_sb(buf_er * output,
		long int n, char *b,
		unsigned char flags, int width, int precision);
unsigned int conv_ub(buf_er *output,
		unsigned long int n, char *b,
		unsigned char flags, int width, int precision);

/**
 * conv_sb - Converts a signed long to an inputted base and stores
 *                 the result to a buffer contained in a struct.
 * @output: A buf_er struct containing a character array.
 * @n: A signed long to be converted.
 * @b: A pointer to a string containing the b to convert to.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_sb(buf_er *output, long int n, char *b,
		unsigned char flags, int width, int precision)
{
	int size;
	char digit, pad = '0';
	unsigned int r = 1;

	for (size = 0; *(b + size);)
		size++;

	if (n >= size || n <= -size)
		r += conv_sb(output, n / size, b,
				flags, width - 1, precision - 1);

	else
	{
		for (; precision > 1; precision--, width--) /* Handle precision */
			r += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				r += _memcpy(output, &pad, 1);
		}
	}

	digit = b[(n < 0 ? -1 : 1) * (n % size)];
	_memcpy(output, &digit, 1);

	return (r);
}

/**
 * conv_ub - Converts an unsigned long to an inputted base and
 *                 stores the result to a buffer contained in a struct.
 * @output: A buf_er struct containing a character array.
 * @n: An unsigned long to be converted.
 * @b: A pointer to a string containing the b to convert to.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_ub(buf_er *output, unsigned long int n, char *b,
		unsigned char flags, int width, int precision)
{
	unsigned int size, r = 1;
	char digit, pad = '0', *lead = "0x";

	for (size = 0; *(b + size);)
		size++;

	if (n >= size)
		r += conv_ub(output, n / size, b,
				flags, width - 1, precision - 1);

	else
	{
		if (((flags >> 5) & 1) == 1) /* Printing a ptr address */
		{
			width -= 2;
			precision -= 2;
		}
		for (; precision > 1; precision--, width--) /* Handle precision */
			r += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; width > 1; width--)
				r += _memcpy(output, &pad, 1);
		}
		if (((flags >> 5) & 1) == 1) /* Print 0x for ptr address */
			r += _memcpy(output, lead, 2);
	}

	digit = b[(n % size)];
	_memcpy(output, &digit, 1);

	return (r);
}
