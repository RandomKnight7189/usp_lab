#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void printFileInfo(const char *filename)
{
    struct stat fileStat;
    if (stat(filename, &fileStat) < 0)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }
    printf("Information for %s\n", filename);
    printf("---------------------------\n");
    printf("File Size: \t\t%ld bytes\n", fileStat.st_size);
    printf("Number of Links: \t%ld\n", fileStat.st_nlink);
    printf("File inode: \t\t%ld\n", fileStat.st_ino);
    printf("\n");
}

int main()
{
    const char *filename = "original.txt";
    const char *hardlink = "hardlink.txt";
    const char *softlink = "softlink.txt";

    // Create an original file
    int fd = open(filename, O_CREAT | O_WRONLY, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }
    write(fd, "This is a test file.\n", 21);
    close(fd);

    // Create a hard link
    if (link(filename, hardlink) < 0)
    {
        perror("link");
        exit(EXIT_FAILURE);
    }

    // Create a soft link
    if (symlink(filename, softlink) < 0)
    {
        perror("symlink");
        exit(EXIT_FAILURE);
    }

    // Print information about the files
    printFileInfo(filename);
    printFileInfo(hardlink);
    printFileInfo(softlink);

    return 0;
}
