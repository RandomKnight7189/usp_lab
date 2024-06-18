#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

void copy_file(const char *source, const char *destination)
{
    int src_fd, dest_fd;
    ssize_t nread;
    char buffer[BUFFER_SIZE];

    src_fd = open(source, O_RDONLY);
    if (src_fd == -1)
    {
        fprintf(stderr, "Error opening source file %s: %s\n", source, strerror(errno));
        exit(EXIT_FAILURE);
    }

    dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1)
    {
        fprintf(stderr, "Error opening/creating destination file %s: %s\n", destination, strerror(errno));
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    while ((nread = read(src_fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (write(dest_fd, buffer, nread) != nread)
        {
            fprintf(stderr, "Error writing to destination file %s: %s\n", destination, strerror(errno));
            close(src_fd);
            close(dest_fd);
            exit(EXIT_FAILURE);
        }
    }

    if (nread == -1)
    {
        fprintf(stderr, "Error reading from source file %s: %s\n", source, strerror(errno));
    }

    close(src_fd);
    close(dest_fd);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    copy_file(argv[1], argv[2]);

    return 0;
}
