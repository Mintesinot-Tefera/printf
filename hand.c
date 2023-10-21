#include "main.h"

unsigned char hand_flags(const char *flag, char *index);
unsigned char hand_length(const char *modifier, char *index);
int hand_width(va_list arg, const char *modifier, char *index);
int hand_precision(va_list arg, const char *modifier, char *index);
unsigned int (*hand_specifiers(const char *specifier))(va_list, buf_er *,
		unsigned char, int, int, unsigned char);

/**
 * hand_flags - Matches flags with corresponding values.
 * @flag: A pointer to a potential string of flags.
 * @index: An index counter for the original format string.
 *
 * Return: If flag characters are matched - a corresponding value.
 *         Otherwise - 0.
 */
unsigned char hand_flags(const char *flag, char *index)
{
	int i, j;
	unsigned char r = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	for (i = 0; flag[i]; i++)
	{
		for (j = 0; flags[j].flag != 0; j++)
		{
			if (flag[i] == flags[j].flag)
			{
				(*index)++;
				if (r == 0)
					r = flags[j].value;
				else
					r |= flags[j].value;
				break;
			}
		}
		if (flags[j].value == 0)
			break;
	}

	return (r);
}

/**
 * hand_length - Matches length modifiers with their corresponding value.
 * @modifier: A pointer to a potential length modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a lenth modifier is matched - its corresponding value.
 *         Otherwise - 0.
 */
unsigned char hand_length(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * hand_width - Matches a width modifier with its corresponding value.
 * @arg: A va_list of arguments.
 * @modifier: A pointer to a potential width modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a width modifier is matched - its value.
 *         Otherwise - 0.
 */
int hand_width(va_list arg, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * hand_precision - Matches a precision modifier with
 *                    its corresponding value.
 * @arg: A va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 * @index: An index counter for the original format string.
 *
 * Return: If a precision modifier is matched - its value.
 *         If the precision modifier is empty, zero, or negative - 0.
 *         Otherwise - -1.
 */
int hand_precision(va_list arg, const char *modifier, char *index)
{
	int value = 0;

	if (*modifier != '.')
		return (-1);

	modifier++;
	(*index)++;

	if ((*modifier <= '0' || *modifier > '9') &&
		 *modifier != '*')
	{
		if (*modifier == '0')
			(*index)++;
		return (0);
	}

	while ((*modifier >= '0' && *modifier <= '9') ||
		   (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 * hand_specifiers - Matches a conversion specifier with
 *                     a corresponding conversion function.
 * @specifier: A pointer to a potential conversion specifier.
 *
 * Return: If a conversion function is matched - a pointer to the function.
 *         Otherwise - NULL.
 */
unsigned int (*hand_specifiers(const char *specifier))(va_list, buf_er *,
		unsigned char, int, int, unsigned char)
{
	int i;
	converter_t converters[] = {
		{'c', conv_c},
		{'s', conv_s},
		{'d', conv_di},
		{'i', conv_di},
		{'%', conv_percent},
		{'b', conv_b},
		{'u', conv_u},
		{'o', conv_o},
		{'x', conv_x},
		{'X', conv_X},
		{'S', conv_S},
		{'p', conv_p},
		{'r', conv_r},
		{'R', conv_R},
		{0, NULL}
	};

	for (i = 0; converters[i].func; i++)
	{
		if (converters[i].specifier == *specifier)
			return (converters[i].func);
	}

	return (NULL);
}
