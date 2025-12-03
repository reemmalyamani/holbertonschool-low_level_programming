#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <elf.h>

/**
 * swap16 - swap 2 bytes
 * @v: value
 *
 * Return: swapped value
 */
uint16_t swap16(uint16_t v)
{
	return ((v << 8) | (v >> 8));
}

/**
 * swap32 - swap 4 bytes
 * @v: value
 *
 * Return: swapped value
 */
uint32_t swap32(uint32_t v)
{
	return (((v & 0x000000FF) << 24) |
		((v & 0x0000FF00) << 8) |
		((v & 0x00FF0000) >> 8) |
		((v & 0xFF000000) >> 24));
}

/**
 * swap64 - swap 8 bytes
 * @v: value
 *
 * Return: swapped value
 */
uint64_t swap64(uint64_t v)
{
	unsigned char *p = (unsigned char *)&v;

	return (((uint64_t)p[0] << 56) |
		((uint64_t)p[1] << 48) |
		((uint64_t)p[2] << 40) |
		((uint64_t)p[3] << 32) |
		((uint64_t)p[4] << 24) |
		((uint64_t)p[5] << 16) |
		((uint64_t)p[6] << 8) |
		((uint64_t)p[7]));
}

/**
 * error - print error message and exit with status 98
 * @m: error message
 */
void error(const char *m)
{
	dprintf(STDERR_FILENO, "%s\n", m);
	exit(98);
}

/**
 * print_magic - print ELF magic bytes (no trailing spaces)
 * @id: ELF identifier array
 */
void print_magic(unsigned char *id)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", id[i]);
		if (i < EI_NIDENT - 1)
			printf(" ");
	}
	printf("\n");
}

