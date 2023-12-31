#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* Flag Modifier Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

/**
 * struct buffer_s - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */
typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buf_er;

/**
 * struct converter_s - A new type defining a converter struct.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
 */
typedef struct conv_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buf_er *,
			unsigned char, int, int, unsigned char);
} conv_t;

/**
 * struct flag_s - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);

/* Conversion Specifier Functions */

unsigned int conv_c(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_s(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_di(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_percent(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_b(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_u(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_o(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_x(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_X(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_S(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_p(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_r(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_R(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_c(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_s(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_di(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_percent(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_b(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_u(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_o(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_x(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_X(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_S(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_p(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_r(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int conv_R(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);

/* Handlers */
unsigned char hand_flags(const char *flags, char *index);
unsigned char hand_length(const char *modifier, char *index);
int hand_width(va_list arg, const char *modifier, char *index);
int hand_precision(va_list arg, const char *modifier, char *index);
unsigned int (*hand_specifiers(const char *specifier))(va_list, buf_er *,
		unsigned char, int, int, unsigned char);

/* Modifiers */
unsigned int pr_width(buf_er *output, unsigned int printed,
		unsigned char flags, int width);
unsigned int pr_str_width(buf_er *output,
		unsigned char flags, int width, int precision, int size);
unsigned int pr_neg_width(buf_er *output, unsigned int printed,
		unsigned char flags, int width);

/* Helper Functions */
buf_er *init_buffer(void);
void free_buffer(buf_er *output);
unsigned int mem_cpy(buf_er *output, const char *src, unsigned int n);
unsigned int conv_sb(buf_er *output, long int num, char *base,
		unsigned char flags, int width, int precision);
unsigned int conv_ubase(buf_er *output, unsigned long int num, char *base,
		unsigned char flags, int width, int precision);

#endif /* MAIN_H */
