#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("File name not entered\n");
        exit(-1);
    }

    struct stat fileStat;

    if (stat(argv[1], &fileStat) < 0)
    {
        fprintf(stderr, "Error getting stats\n");
        exit(-1);
    }

    printf("Information of %s\n\n", argv[1]);
    printf("File Size : %ld bytes\n", fileStat.st_size);
    printf("Number of links : %ld\n", fileStat.st_nlink);
    printf("File inode : %ld\n", fileStat.st_ino);
    printf("Access time : %ld\n", fileStat.st_atime);
    printf("Modification time : %ld\n", fileStat.st_mtime);

    return 0;
}