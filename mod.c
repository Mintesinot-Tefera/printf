#include "main.h"

unsigned int pr_width(buf_er * output, unsigned int printed,
		unsigned char flags, int width);
unsigned int pr_str_width(buf_er *output,
		unsigned char flags, int width, int precision, int size);
unsigned int pr_neg_width(buf_er *output, unsigned int printed,
		unsigned char flags, int width);

/**
 * pr_width - Stores leading spaces to a buffer for a width modifier.
 * @output: A buffer_t struct containing a character array.
 * @printed: The current number of characters already printed to output
 *           for a given number specifier.
 * @flags: Flag modifiers.
 * @width: Width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int pr_width(buf_er *output, unsigned int printed,
		unsigned char flags, int width)
{
	unsigned int r = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		for (width -= printed; width > 0;)
			r += mem_cpy(output, &width, 1);
	}

	return (r);
}

/**
 * pr_str_width - Stores leading spaces to a buffer for a width modifier.
 * @output: A buf_er struct containing a character array.
 * @flags: Flag modifiers.
 * @width: Width modifier.
 * @precision: Precision modifier.
 * @size: The size of the string.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int pr_str_width(buf_er *output,
		unsigned char flags, int width, int precision, int size)
{
	unsigned int r = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		width -= (precision == -1) ? size : precision;
		for (; width > 0; width--)
			r += mem_cpy(output, &width, 1);
	}

	return (r);
}

/**
 * pr_neg_width - Stores trailing spaces to a buffer for a '-' flag.
 * @output: A buf_er struct containing a character array.
 * @printed: The current number of bytes already stored to output
 *           for a given specifier.
 * @flags: A flag modifiers.
 * @width: Width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int pr_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int width)
{
	unsigned int r = 0;
	char width = ' ';

	if (NEG_FLAG == 1)
	{
		for (width -= printed; width > 0; width--)
			r += _memcpy(output, &width, 1);
	}

	return (r);
}
