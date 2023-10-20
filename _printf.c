#include "main.h"

void clup(va_list arg, buf_er *output);
int run_printf(const char *format, va_list arg, buf_er *output);
int _printf(const char *format, ...);
/**
 * clup - Peforms cleanup operations for _printf.
 * @arg: A va_list of arguments provided to _printf.
 * @output: A buf_er struct.
 */
void clup(va_list arg, buf_er *output)
{
	va_end(arg);
	write(1, output->start, output->len);
	free_buffer(output);
}
/**
 * run_printf - Reads through the format string for _printf.
 * @format: Character string to print - may contain directives.
 * @output: A buf_er struct containing a buffer.
 * @arg: A va_list of arguments.
 *
 * Return: The number of characters stored to output.
 */
int run_printf(const char *format, va_list arg, buf_er *output)
{
	int i, width, precision, r = 0;
	char tmp;
	unsigned char flags, len;
	unsigned int (*f)(va_list, buf_er *,
			unsigned char, int, int, unsigned char);

	for (i = 0; *(format + i); i++)
	{
		len = 0;
		if (*(format + i) == '%')
		{
			tmp = 0;
			flags = handle_flags(format + i + 1, &tmp);
			width = handle_width(arg, format + i + tmp + 1, &tmp);
			precision = handle_precision(arg, format + i + tmp + 1,
					&tmp);
			len = handle_length(format + i + tmp + 1, &tmp);

			f = handle_specifiers(format + i + tmp + 1);
			if (f != NULL)
			{
				i += tmp + 1;
				r += f(arg, output, flags, width, precision, len);
				continue;
			}
			else if (*(format + i + tmp + 1) == '\0')
			{
				r = -1;
				break;
		}
	}
	r += mem_cpy(output, (format + i), 1);
		i += (len != 0) ? 1 : 0;
	}
	/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	buf_er *output;
	va_list arg;
	int r;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(arg, format);

	r = run_printf(format, arg, output);

	return (r);
}
