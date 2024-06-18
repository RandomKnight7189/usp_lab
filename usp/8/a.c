#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

int main()
{
    DIR *dp;
    struct dirent *dir;
    int fd, n;

    dp = opendir(".");
    if (dp)
    {
        while ((dir = readdir(dp)))
        {
            fd = open(dir->d_name, O_RDONLY);
            n = lseek(fd, (off_t)0, SEEK_END);
            if (!n)
            {
                unlink(dir->d_name);
            }
        }
    }
}