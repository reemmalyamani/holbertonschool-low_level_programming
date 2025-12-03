#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>

uint16_t swap16(uint16_t v)
{
    return (v << 8) | (v >> 8);
}

uint32_t swap32(uint32_t v)
{
    return ((v & 0x000000FF) << 24) |
           ((v & 0x0000FF00) << 8) |
           ((v & 0x00FF0000) >> 8) |
           ((v & 0xFF000000) >> 24);
}

uint64_t swap64(uint64_t v)
{
    unsigned char *p = (unsigned char *)&v;

    return ((uint64_t)p[0] << 56) |
           ((uint64_t)p[1] << 48) |
           ((uint64_t)p[2] << 40) |
           ((uint64_t)p[3] << 32) |
           ((uint64_t)p[4] << 24) |
           ((uint64_t)p[5] << 16) |
           ((uint64_t)p[6] << 8)  |
           ((uint64_t)p[7]);
}

void error(const char *m)
{
    dprintf(STDERR_FILENO, "%s\n", m);
    exit(98);
}

void print_magic(unsigned char *id)
{
    int i;

    printf("  Magic:   ");
    for (i = 0; i < EI_NIDENT; i++)
        printf("%02x ", id[i]);
    printf("\n");
}

void print_osabi(unsigned char v)
{
    printf("  OS/ABI:                            ");

    switch (v)
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

        /* Missing readelf OSABI constants (must include manually) */
        case 12:                  printf("UNIX - OpenBSD\n"); break;   /* 0x0C */
        case 17:                  printf("UNIX - CloudABI\n"); break;  /* 0x11 */
        case 83:                  printf("UNIX - Sortix\n"); break;    /* 0x53 */

        default:                  printf("<unknown: %x>\n", v);
    }
}

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
    if (cls == ELFCLASS32) printf("ELF32\n");
    else if (cls == ELFCLASS64) printf("ELF64\n");
    else printf("<unknown: %x>\n", cls);

    printf("  Data:                              ");
    if (end == ELFDATA2LSB) printf("2's complement, little endian\n");
    else if (end == ELFDATA2MSB) printf("2's complement, big endian\n");
    else printf("<unknown: %x>\n", end);

    printf("  Version:                           %d", id[EI_VERSION]);
    if (id[EI_VERSION] == EV_CURRENT)
        printf(" (current)");
    printf("\n");

    print_osabi(id[EI_OSABI]);

    printf("  ABI Version:                       %d\n", id[EI_ABIVERSION]);

    if (lseek(fd, 0, SEEK_SET) == -1)
        error("Error: Can't lseek");

    if (cls == ELFCLASS64)
    {
        uint16_t t;
        uint64_t e;

        r = read(fd, &h64, sizeof(h64));
        if (r != sizeof(h64))
            error("Error: Can't read ELF64 header");

        t = h64.e_type;
        if (end == ELFDATA2MSB)
            t = swap16(t);

        printf("  Type:                              ");
        if (t == ET_NONE) printf("NONE (None)\n");
        else if (t == ET_REL) printf("REL (Relocatable file)\n");
        else if (t == ET_EXEC) printf("EXEC (Executable file)\n");
        else if (t == ET_DYN) printf("DYN (Shared object file)\n");
        else if (t == ET_CORE) printf("CORE (Core file)\n");
        else printf("<unknown: %x>\n", t);

        e = h64.e_entry;
        if (end == ELFDATA2MSB)
            e = swap64(e);

        printf("  Entry point address:               %#lx\n",
               (unsigned long)e);
    }
    else
    {
        uint16_t t;
        uint32_t e;

        r = read(fd, &h32, sizeof(h32));
        if (r != sizeof(h32))
            error("Error: Can't read ELF32 header");

        t = h32.e_type;
        if (end == ELFDATA2MSB)
            t = swap16(t);

        printf("  Type:                              ");
        if (t == ET_NONE) printf("NONE (None)\n");
        else if (t == ET_REL) printf("REL (Relocatable file)\n");
        else if (t == ET_EXEC) printf("EXEC (Executable file)\n");
        else if (t == ET_DYN) printf("DYN (Shared object file)\n");
        else if (t == ET_CORE) printf("CORE (Core file)\n");
        else printf("<unknown: %x>\n", t);

        e = h32.e_entry;
        if (end == ELFDATA2MSB)
            e = swap32(e);

        printf("  Entry point address:               %#x\n", e);
    }

    close(fd);
    return 0;
}
