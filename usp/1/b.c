#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd;
    pid_t pid;
    char buffer[100];

    fd = open(argv[1], O_RDONLY);

    if (fd < 0)
    {
        fprintf(stderr, "Failed to open file\n");
        exit(-1);
    }

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork Failed\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        ssize_t bytesRead = read(fd, buffer, 5);

        if (bytesRead < 0)
        {
            fprintf(stderr, "Child failed to read from file\n");
            exit(-1);
        }
        buffer[bytesRead] = '\0';
        printf("Child read : %s\n", buffer);
    }
    else
    {
        wait(NULL);
        ssize_t bytesRead = read(fd, buffer, 10);

        if (bytesRead < 0)
        {
            fprintf(stderr, "Child failed to read from file\n");
            exit(-1);
        }
        buffer[bytesRead] = '\0';
        printf("Parent read : %s\n", buffer);
    }
    close(fd);

    return 0;
}