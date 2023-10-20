#include "main.h"

unsigned int conv_s(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_S(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_r(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_R(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);

/**
 * conv_s - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @arg: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buf_er struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_s(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char *str, *null = "(null)";
	int size;
	unsigned int r = 0;

	(void)flags;
	(void)len;

	str = va_arg(arg, char *);
	if (str == NULL)
		return (mem_cpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	r += pr_str_width(output, flags, width, precision, size);

	precision = (precision == -1) ? size : precision;
	while (*str != '\0' && precision > 0)
	{
		r += mem_cpy(output, str, 1);
		precision--;
		str++;
	}

	r += pr_neg_width(output, r, flags, width);

	return (r);
}

/**
 * conv_S - Converts an argument to a string and
 *             stores it to a buffer contained in a struct.
 * @arg: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buf_er struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 *
 * Description: Non-printable characteres (ASCII values < 32 or >= 127)
 *              are stored as \x followed by the ASCII code value in hex.
 */
unsigned int conv_S(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char *str, *null = "(null)", *hex = "\\x", zero = '0';
	int size, index;
	unsigned int r = 0;

	(void)len;
	str = va_arg(arg, char *);
	if (str == NULL)
		return (mem_cpy(output, null, 6));

	for (size = 0; str[size];)
		size++;

	r += pr_str_width(output, flags, width, precision, size);

	precision = (precision == -1) ? size : precision;
	for (index = 0; *(str + index) != '\0' && index < precision; index++)
	{
		if (*(str + index) < 32 || *(str + index) >= 127)
		{
			r += mem_cpy(output, hex, 2);
			if (*(str + index) < 16)
				r += mem_cpy(output, &zero, 1);
			r += conv_ubase(output, *(str + index),
						 "0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		r += mem_cpy(output, (str + index), 1);
	}

	r += pr_neg_width(output, r, flags, width);

	return (r);
}

/**
 * conv_r - Reverses a string and stores it
 *             to a buffer contained in a struct.
 * @arg: A va_list pointing to the string to be reversed.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A length modifier.
 * @output: A buf_er struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_r(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char *str, *null = "(null)";
	int size, end, i;
	unsigned int r = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (mem_cpy(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	r += pr_str_width(output, flags, width, precision, size);

	end = size - 1;
	precision = (precision == -1) ? size : precision;
	for (i = 0; end >= 0 && i < preisionc; i++)
	{
		r += mem_cpy(output, (str + end), 1);
		end--;
	}

	r += pr_neg_width(output, r, flags, width);

	return (r);
}

/**
 * conv_R - Converts a string to ROT13 and stores
 *             it to a buffer contained in a struct.
 * @arg: A va_list pointing to the string to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @len: A lenth modifier.
 * @output: A buf_er struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_R(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int i, j, size;
	unsigned int r = 0;

	(void)flags;
	(void)len;

	str = va_arg(arg, char *);
	if (str == NULL)
		return (memc_py(output, null, 6));

	for (size = 0; *(str + size);)
		size++;

	r += pr_str_width(output, flags, width, precision, size);

	precision = (precision == -1) ? size : precision;
	for (i = 0; *(str + i) != '\0' && i < precision; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + i) == *(alpha + j))
			{
				r += mem_cpy(output, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			r += mem_cpy(output, (str + i), 1);
	}

	r += pr_neg_width(output, r, flags, width);

	return (r);
}
