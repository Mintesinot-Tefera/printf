#include "main.h"

unsigned int conv_di(va_list arg, buf_er * output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_b(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_u(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_o(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);

/**
 * conv_di - Converts an argument to a signed int and
 *              stores it to a buffer contained in a struct.
 * @arg: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: Width modifier.
 * @precision: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_di(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	long int d, copy;
	unsigned int r = 0, count = 0;
	char pad, space = ' ', neg = '-', plus = '+';

	if (len == LONG)
		d = va_arg(arg, long int);
	else
		d = va_arg(arg, int);
	if (len == SHORT)
		d = (short)d;

	/* Handle space flag */
	if (SPACE_FLAG == 1 && d >= 0)
		r += _memcpy(output, &space, 1);

	if (precision <= 0 && NEG_FLAG == 0) /* Handle width  */
	{
		if (d == LONG_MIN)
			count += 19;
		else
		{
			for (copy = (d < 0) ? -d : d; copy > 0; copy /= 10)
				count++;
		}
		count += (d == 0) ? 1 : 0;
		count += (d < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && d >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && d >= 0) ? 1 : 0;

		/* Handle plus flag when zero flag is active */
		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && d >= 0)
			ret += _memcpy(output, &plus, 1);
		/*Print negative sign when zero flag is active */
		if (ZERO_FLAG == 1 && d < 0)
			r += _memcpy(output, &neg, 1);

		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (width -= count; width > 0; width--)
			r += _memcpy(output, &pad, 1);
	}

	/* Print negative sign when zero flag is not active */
	if (ZERO_FLAG == 0 && d < 0)
		r += _memcpy(output, &neg, 1);
	/* Handle plus flag when zero flag is not active */
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && d >= 0))
		r += _memcpy(output, &plus, 1);

	if (!(d == 0 && precision == 0))
		r += conv_sb(output, d, "0123456789",
				flags, 0, precision);

	r += print_neg_width(output, r, flags, width);

	return (r);
}

/**
 * conv_b - Converts an unsigned int argument to binary
 *             and stores it to a buffer contained in a struct.
 * @arg: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: Width modifier.
 * @precision: Precision modifier.
 * @len:Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_b(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	unsigned int num;

	num = va_arg(arg, unsigned int);

	(void)len;

	return (conv_ubase(output, num, "01", flags, width, precision));
}

/**
 * conv_o - Converts an unsigned int to octal and
 *             stores it to a buffer contained in a struct.
 * @arg: A va_list poinitng to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_o(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	unsigned long int num;
	unsigned int r = 0;
	char zero = '0';

	if (len == LONG)
		num = va_arg(arg, unsigned long int);
	else
		num = va_arg(arg, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (HASH_FLAG == 1 && num != 0)
		r += _memcpy(output, &zero, 1);

	if (!(num == 0 && precision == 0))
		r += conv_ubase(output, num, "01234567",
				flags, width, precision);

	r += print_neg_width(output, r, flags, width);

	return (r);
}

/**
 * conv_u - Converts an unsigned int argument to decimal and
 *               stores it to a buffer contained in a struct.
 * @arg: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: Width modifier.
 * @precision: Precision modifier.
 * @len: Length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int conv_u(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len)
{
	unsigned long int num;
	unsigned int r = 0;

	if (len == LONG)
		num = va_arg(arg, unsigned long int);
	else
		num = va_arg(arg, unsigned int);
	if (len == SHORT)
		num = (unsigned short)num;

	if (!(num == 0 && precision == 0))
		r += conv_ubase(output, num, "0123456789",
				flags, width, precision);

	r += print_neg_width(output, r, flags, width);

	return (r);
}
