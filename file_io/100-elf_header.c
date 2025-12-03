#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

/* Print error and exit */
void print_error(const char *msg)
{
    dprintf(STDERR_FILENO, "%s\n", msg);
    exit(98);
}

/* Print magic bytes */
void print_magic(unsigned char *e_ident)
{
    int i;

    printf("  Magic:   ");
    for (i = 0; i < EI_NIDENT; i++)
    {
        printf("%02x", e_ident[i]);
        if (i < EI_NIDENT - 1)
            printf(" ");
    }
    printf("\n");
}

int main(int argc, char **argv)
{
    int fd;
    Elf64_Ehdr header;

    /* Check arguments */
    if (argc != 2)
        print_error("Usage: elf_header elf_filename");

    /* Open file */
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        print_error("Error: Can't read file");

    /* Read header */
    if (read(fd, &header, sizeof(header)) != sizeof(header))
        print_error("Error: Can't read ELF header");

    /* Verify ELF magic */
    if (header.e_ident[EI_MAG0] != ELFMAG0 ||
        header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 ||
        header.e_ident[EI_MAG3] != ELFMAG3)
        print_error("Error: Not an ELF file");

    /* HEADER TITLE */
    printf("ELF Header:\n");

    /* MAGIC */
    print_magic(header.e_ident);

    /* CLASS */
    printf("  Class:                             ");
    switch (header.e_ident[EI_CLASS])
    {
        case ELFCLASS32: printf("ELF32\n"); break;
        case ELFCLASS64: printf("ELF64\n"); break;
        default: printf("<unknown: %x>\n", header.e_ident[EI_CLASS]);
    }

    /* DATA */
    printf("  Data:                              ");
    switch (header.e_ident[EI_DATA])
    {
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;
        default:
            printf("<unknown: %x>\n", header.e_ident[EI_DATA]);
    }

    /* VERSION */
    printf("  Version:                           %d (current)\n",
           header.e_ident[EI_VERSION]);

    /* OS/ABI */
    printf("  OS/ABI:                            ");
    switch (header.e_ident[EI_OSABI])
    {
        case ELFOSABI_SYSV: printf("UNIX - System V\n"); break;
        case ELFOSABI_NETBSD: printf("UNIX - NetBSD\n"); break;
        case ELFOSABI_SOLARIS: printf("UNIX - Solaris\n"); break;
        default: printf("<unknown: %x>\n", header.e_ident[EI_OSABI]);
    }

    /* ABI VERSION */
    printf("  ABI Version:                       %d\n",
           header.e_ident[EI_ABIVERSION]);

    /* TYPE */
    printf("  Type:                              ");
    switch (header.e_type)
    {
        case ET_EXEC: printf("EXEC (Executable file)\n"); break;
        case ET_DYN:  printf("DYN (Shared object file)\n"); break;
        case ET_REL:  printf("REL (Relocatable file)\n"); break;
        default: printf("<unknown: %x>\n", header.e_type);
    }

    /* ENTRY POINT */
    printf("  Entry point address:               %#lx\n",
           (unsigned long) header.e_entry);

    close(fd);
    return (0);
}
