#include <stdio.h>
#include <elf.h>

/**
 * print_osabi - print OS/ABI
 * @v: value
 */
void print_osabi(unsigned char v)
{
	printf("  OS/ABI:                            ");

	switch (v)
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("UNIX - Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("UNIX - FreeBSD\n");
		break;
	case 12:
		printf("UNIX - OpenBSD\n");
		break;
	case 17:
		printf("UNIX - CloudABI\n");
		break;
	case 83:
		printf("UNIX - Sortix\n");
		break;
	default:
		printf("<unknown: %x>\n", v);
		break;
	}
}
