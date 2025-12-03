#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

uint16_t swap16(uint16_t val)
{
    return (val << 8) | (val >> 8);
}

uint32_t swap32(uint32_t val)
{
    return ((val & 0x000000FF) << 24) |
           ((val & 0x0000FF00) << 8) |
           ((val & 0x00FF0000) >> 8) |
           ((val & 0xFF000000) >> 24);
}

uint64_t swap64(uint64_t val)
{
    uint64_t b0, b1, b2, b3, b4, b5, b6, b7;

    b0 = (val & 0x00000000000000FFULL) << 56;
    b1 = (val & 0x000000000000FF00ULL) << 40;
    b2 = (val & 0x0000000000FF0000ULL) << 24;
    b3 = (val & 0x00000000FF000000ULL) << 8;
    b4 = (val & 0x000000FF00000000ULL) >> 8;
    b5 = (val & 0x0000FF0000000000ULL) >> 24;
    b6 = (val & 0x00FF000000000000ULL) >> 40;
    b7 = (val & 0xFF00000000000000ULL) >> 56;

    return b0 | b1 | b2 | b3 | b4 | b5 | b6 | b7;
}

void print_error(const char *msg)
{
    dprintf(STDERR_FILENO, "%s\n", msg);
    exit(98);
}

void print_magic(unsigned char *e_ident)
{
    int i;

    printf("  Magic:   ");
    for (i = 0; i < EI_NIDENT; i++)
        printf("%02x ", e_ident[i]);
    printf("\n");
}

void print_osabi(unsigned char osabi)
{
    printf("  OS/ABI:                            ");

    switch (osabi)
    {
        case ELFOSABI_SYSV:       printf("UNIX - System V\n"); break;
        case ELFOSABI_HPUX:       printf("HP-UX\n"); break;
        case ELFOSABI_NETBSD:     printf("UNIX - NetBSD\n"); break;
        case ELFOSABI_LINUX:      printf("UNIX - Linux\n"); break;
        case ELFOSABI_SOLARIS:    printf("UNIX - Solaris\n"); break;
        case ELFOSABI_IRIX:       printf("UNIX - IRIX\n"); break;
        case ELFOSABI_FREEBSD:    printf("UNIX - FreeBSD\n"); break;
        case ELFOSABI_TRU64:      printf("UNIX - TRU64\n"); break;
        case ELFOSABI_ARM:        printf("ARM\n"); break;
        case ELFOSABI_STANDALONE: printf("Standalone App\n"); break;
        default:                  printf("<unknown: %x>\n", osabi);
    }
}

int main(int argc, char **argv)
{
    int fd;
    unsigned char ident[EI_NIDENT];
    Elf64_Ehdr header64;
    Elf32_Ehdr header32;
    int elf_class, endian;
    ssize_t r;

    if (argc != 2)
        print_error("Usage: elf_header elf_filename");

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        print_error("Error: Can't read file");

    r = read(fd, ident, EI_NIDENT);
    if (r != EI_NIDENT)
        print_error("Error: Can't read ELF header");

    if (ident[EI_MAG0] != ELFMAG0 ||
        ident[EI_MAG1] != ELFMAG1 ||
        ident[EI_MAG2] != ELFMAG2 ||
        ident[EI_MAG3] != ELFMAG3)
        print_error("Error: Not an ELF file");

    printf("ELF Header:\n");
    print_magic(ident);

    elf_class = ident[EI_CLASS];
    endian = ident[EI_DATA];

    printf("  Class:                             ");
    if (elf_class == ELFCLASS32)
        printf("ELF32\n");
    else if (elf_class == ELFCLASS64)
        printf("ELF64\n");
    else
        printf("<unknown: %x>\n", elf_class);

    printf("  Data:                              ");
    if (endian == ELFDATA2LSB)
        printf("2's complement, little endian\n");
    else if (endian == ELFDATA2MSB)
        printf("2's complement, big endian\n");
    else
        printf("<unknown: %x>\n", endian);

    printf("  Version:                           %d", ident[EI_VERSION]);
    if (ident[EI_VERSION] == EV_CURRENT)
        printf(" (current)");
    printf("\n");

    print_osabi(ident[EI_OSABI]);

    printf("  ABI Version:                       %d\n", ident[EI_ABIVERSION]);

    if (lseek(fd, 0, SEEK_SET) == -1)
        print_error("Error: Can't lseek");

    if (elf_class == ELFCLASS64)
    {
        uint16_t type;
        uint64_t entry;

        r = read(fd, &header64, sizeof(header64));
        if (r != sizeof(header64))
            print_error("Error: Can't read ELF64 header");

        type = header64.e_type;
        if (endian == ELFDATA2MSB)
            type = swap16(type);

        printf("  Type:                              ");
        switch (type)
        {
            case ET_NONE: printf("NONE (Unknown type)\n"); break;
            case ET_REL:  printf("REL (Relocatable file)\n"); break;
            case ET_EXEC: printf("EXEC (Executable file)\n"); break;
            case ET_DYN:  printf("DYN (Shared object file)\n"); break;
            case ET_CORE: printf("CORE (Core file)\n"); break;
            default:      printf("<unknown: %x>\n", type);
        }

        entry = header64.e_entry;
        if (endian == ELFDATA2MSB)
            entry = swap64(entry);

        printf("  Entry point address:               %#lx\n",
               (unsigned long)entry);
    }
    else
    {
        uint16_t type;
        uint32_t entry;

        r = read(fd, &header32, sizeof(header32));
        if (r != sizeof(header32))
            print_error("Error: Can't read ELF32 header");

        type = header32.e_type;
        if (endian == ELFDATA2MSB)
            type = swap16(type);

        printf("  Type:                              ");
        switch (type)
        {
            case ET_NONE: printf("NONE (Unknown type)\n"); break;
            case ET_REL:  printf("REL (Relocatable file)\n"); break;
            case ET_EXEC: printf("EXEC (Executable file)\n"); break;
            case ET_DYN:  printf("DYN (Shared object file)\n"); break;
            case ET_CORE: printf("CORE (Core file)\n"); break;
            default:      printf("<unknown: %x>\n", type);
        }

        entry = header32.e_entry;
        if (endian == ELFDATA2MSB)
            entry = swap32(entry);

        printf("  Entry point address:               %#x\n", entry);
    }

    close(fd);
    return 0;
}
