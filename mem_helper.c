#include "main.h"

unsigned int mem_cpy(buf_er *output, const char *src, unsigned int n);
void free_buffer(buffer_t *output);
buf_er *init_buffer(void);

/**
 * mem_cpy - Copies n bytes from memory area src to
 *           the buffer contained in a buffer_t struct.
 * @output: A buffer_t struct.
 * @src: A pointer to the memory area to copy.
 * @n: The number of bytes to be copied.
 *
 * Return: The number of bytes copied.
 */
unsigned int mem_cpy(buf_er *output, const char *src, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
	{
		*(output->buffer) = *(src + index);
		(output->len)++;

		if (output->len == 1024)
		{
			write(1, output->start, output->len);
			output->buffer = output->start;
			output->len = 0;
		}

		else
			(output->buffer)++;
	}

	return (n);
}

/**
 * free_buffer - Frees a buf_er struct.
 * @output: The buf_er struct to be freed.
 */
void free_buffer(buf_er *output)
{
	free(output->start);
	free(output);
}

/**
 * init_buffer - Initializes a variable of struct type buf_er.
 *
 * Return: A pointer to the initialized buf_er.
 */
buf_er *init_buffer(void)
{
	buf_er *output;

	output = malloc(sizeof(buf_er));
	if (output == NULL)
		return (NULL);

	output->buffer = malloc(sizeof(char) * 1024);
	if (output->buffer == NULL)
	{
		free(output);
		return (NULL);
	}

	output->start = output->buffer;
	output->len = 0;

	return (output);
}
