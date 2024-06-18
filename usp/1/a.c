#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int src, n;
    char buff;
    int filesize;

    if (argc != 2)
    {
        fprintf(stderr, "usage <source>");
        exit(-1);
    }

    if ((src = open(argv[1], O_RDONLY)) < 0)
    {
        fprintf(stderr, "Can't open file source\n");
        exit(-1);
    }

    filesize = lseek(src, (off_t)0, SEEK_END);
    printf("Source file size is %d\n", filesize);

    for (int i = filesize - 1; i >= 0; i--)
    {
        lseek(src, (off_t)i, SEEK_SET);

        if ((n = read(src, &buff, 1)) != 1)
        {
            fprintf(stderr, "Can't read 1 byte\n");
            exit(-1);
        }

        printf("%c", buff);
    }

    close(src);

    return 0;
}