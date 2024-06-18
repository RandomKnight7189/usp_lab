#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    mode_t new_mask = 0022; // New mask: rw-r--r--
    mode_t old_mask = umask(new_mask);
    printf("Old umask: %03o\n", old_mask);
    printf("New umask: %03o\n", new_mask);

    int fd = open("example.txt", O_CREAT | O_WRONLY, 0666);
    if (fd < 0)
    {
        perror("Failed to create file");
        exit(EXIT_FAILURE);
    }
    close(fd);

    printf("File 'example.txt' created with umask %03o\n", new_mask);

    // Change file permissions to rwxr-xr--
    if (chmod("example.txt", S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH) < 0)
    {
        perror("chmod error");
        exit(EXIT_FAILURE);
    }

    printf("Permissions of 'example.txt' changed to rwxr-xr--\n");

    return 0;
}
