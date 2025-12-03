#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

uint16_t swap16(uint16_t v);
uint32_t swap32(uint32_t v);
uint64_t swap64(uint64_t v);
void error(const char *m);
void print_magic(unsigned char *id);
void print_osabi(unsigned char v);

/**
 * main - display ELF header information
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success
 */
int main(int ac, char **av)
{
	int fd;
	unsigned char id[EI_NIDENT];
	Elf64_Ehdr h64;
	Elf32_Ehdr h32;
	ssize_t r;
	int cls, end;

	if (ac != 2)
		error("Usage: elf_header elf_filename");

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		error("Error: Can't read file");

	r = read(fd, id, EI_NIDENT);
	if (r != EI_NIDENT)
		error("Error: Can't read ELF header");

	if (id[EI_MAG0] != ELFMAG0 ||
	    id[EI_MAG1] != ELFMAG1 ||
	    id[EI_MAG2] != ELFMAG2 ||
	    id[EI_MAG3] != ELFMAG3)
		error("Error: Not an ELF file");

	printf("ELF Header:\n");
	print_magic(id);

	cls = id[EI_CLASS];
	end = id[EI_DATA];

	printf("  Class:                             ");
	if (cls == ELFCLASS32)
		printf("ELF32\n");
	else if (cls == ELFCLASS64)
		printf("ELF64\n");
	else
		printf("<unknown: %x>\n", cls);

	printf("  Data:                              ");
	if (end == ELFDATA2LSB)
		printf("2's complement, little endian\n");
	else if (end == ELFDATA2MSB)
		printf("2's complement, big endian\n");
	else
		printf("<unknown: %x>\n", end);

	printf("  Version:                           %d",
	       id[EI_VERSION]);
	if (id[EI_VERSION] == EV_CURRENT)
		printf(" (current)");
	printf("\n");

	print_osabi(id[EI_OSABI]);

	printf("  ABI Version:                       %d\n",
	       id[EI_ABIVERSION]);

	if (lseek(fd, 0, SEEK_SET) == -1)
		error("Error: Can't lseek");

	if (cls == ELFCLASS64)
	{
		r = read(fd, &h64, sizeof(h64));
		if (r != sizeof(h64))
			error("Error: Can't read ELF64 header");

		printf("  Type:                              ");
		if (h64.e_type == ET_EXEC)
			printf("EXEC (Executable file)\n");
		else if (h64.e_type == ET_DYN)
			printf("DYN (Shared object file)\n");
		else if (h64.e_type == ET_REL)
			printf("REL (Relocatable file)\n");
		else if (h64.e_type == ET_CORE)
			printf("CORE (Core file)\n");
		else
			printf("<unknown: %x>\n", h64.e_type);

		printf("  Entry point address:               %#lx\n",
		       (unsigned long)h64.e_entry);
	}
	else
	{
		r = read(fd, &h32, sizeof(h32));
		if (r != sizeof(h32))
			error("Error: Can't read ELF32 header");

		printf("  Type:                              ");
		if (h32.e_type == ET_EXEC)
			printf("EXEC (Executable file)\n");
		else if (h32.e_type == ET_DYN)
			printf("DYN (Shared object file)\n");
		else if (h32.e_type == ET_REL)
			printf("REL (Relocatable file)\n");
		else if (h32.e_type == ET_CORE)
			printf("CORE (Core file)\n");
		else
			printf("<unknown: %x>\n", h32.e_type);

		printf("  Entry point address:               %#x\n",
		       h32.e_entry);
	}

	close(fd);
	return (0);
}
