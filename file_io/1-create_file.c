#include "main.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * create_file - creates a file
 * @filename: name of the file
 * @text_content: NULL-terminated string to write
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
    int fd, w, len = 0;

    if (filename == NULL)
        return (-1);

    if (text_content != NULL)
    {
        while (text_content[len])
            len++;
    }

    fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1)
        return (-1);

    if (len > 0)
    {
        w = write(fd, text_content, len);
        if (w == -1 || w != len)
        {
            close(fd);
            return (-1);
        }
    }

    close(fd);
    return (1);
}
