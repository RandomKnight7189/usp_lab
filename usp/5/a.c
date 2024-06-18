#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <utime.h>
#include <time.h>

void print_file_times(const char *filename)
{
    struct stat statbuf;

    if (stat(filename, &statbuf) < 0)
    {
        perror("stat error");
        return;
    }

    printf("File: %s\n", filename);
    printf("Access time: %s", ctime(&statbuf.st_atime));
    printf("Modification time: %s\n", ctime(&statbuf.st_mtime));
}

int main(int argc, char *argv[])
{
    struct stat statbuf;
    struct utimbuf timebuf;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source file> <destination file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Print initial times of destination file
    printf("Before copying:\n");
    print_file_times(argv[2]);

    // Fetch current times from the source file
    if (stat(argv[1], &statbuf) < 0)
    {
        perror("stat error on source file");
        exit(EXIT_FAILURE);
    }

    // Set access and modification times for utimbuf structure
    timebuf.actime = statbuf.st_atime;
    timebuf.modtime = statbuf.st_mtime;

    // Apply the times to the destination file
    if (utime(argv[2], &timebuf) < 0)
    {
        perror("utime error on destination file");
        exit(EXIT_FAILURE);
    }

    // Print times after copying
    printf("After copying:\n");
    print_file_times(argv[2]);

    return 0;
}
