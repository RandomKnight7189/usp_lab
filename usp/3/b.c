#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    struct dirent *dir;
    struct stat fileStat;

    DIR *dp;
    dp = opendir(".");

    if (dp)
    {
        while (dir = readdir(dp))
        {
            stat(dir->d_name, &fileStat);
            printf("File Size : %ld bytes\n", fileStat.st_size);
            printf("Number of links : %ld\n", fileStat.st_nlink);
            printf("File inode : %ld\n", fileStat.st_ino);
            printf("Access time : %ld\n", fileStat.st_atime);
            printf("Modification time : %ld\n", fileStat.st_mtime);
        }
    }
}