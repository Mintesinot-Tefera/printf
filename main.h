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
} buffer_t;

/**
 * struct converter_s - A new type defining a converter struct.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
 */
typedef struct converter_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} converter_t;

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
unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int convert_S(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int convert_p(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int convert_r(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);
unsigned int convert_R(va_list arg, buf_er *output,
		unsigned char flags, int width, int precision, unsigned char len);

/* Handlers */
unsigned char handle_flags(const char *flags, char *index);
unsigned char handle_length(const char *modifier, char *index);
int handle_width(va_list arg, const char *modifier, char *index);
int handle_precision(va_list arg, const char *modifier, char *index);
unsigned int (*handle_specifiers(const char *specifier))(va_list, buf_er *,
		unsigned char, int, int, unsigned char);

/* Modifiers */
unsigned int print_width(buf_er *output, unsigned int printed,
		unsigned char flags, int width);
unsigned int print_string_width(buf_er *output,
		unsigned char flags, int width, int precision, int size);
unsigned int print_neg_width(buf_er *output, unsigned int printed,
		unsigned char flags, int width);

/* Helper Functions */
buf_fer *init_buffer(void);
void free_buffer(buf_er *output);
unsigned int _memcpy(buf_er *output, const char *src, unsigned int n);
unsigned int conv_sb(buf_er *output, long int num, char *base,
		unsigned char flags, int width, int precision);
unsigned int conv_ub(buf_er *output, unsigned long int num, char *base,
		unsigned char flags, int width, int precision);

#endif /* MAIN_H */
