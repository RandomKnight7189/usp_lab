#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int fd;
    char buffer[255];
    struct flock fvar;
    if (argc == 1)
    {
        printf("No arguments specified\n");
        return -1;
    }
    if ((fd = open(argv[1], O_RDWR)) == -1)
    {
        fprintf(stderr, "Could not open file\n");
        exit(1);
    }
    fvar.l_type = F_WRLCK;
    fvar.l_whence = SEEK_END;
    fvar.l_start = SEEK_END - 100;
    fvar.l_len = 100;
    printf("Press ENTER to set lock\n");
    getchar();
    printf("Trying to get lock...\n");

    if ((fcntl(fd, F_SETLK, &fvar)) == -1)
    {
        fcntl(fd, F_GETLK, &fvar);
        printf("Process already locked by: %d\n", fvar.l_pid);
        return -1;
    }
    printf("locked\n");

    if ((lseek(fd, SEEK_END - 50, SEEK_END)) == -1)
    {
        fprintf(stderr, "lseek\n");
        exit(1);
    }

    if (read(fd, buffer, 100) == -1)
    {
        fprintf(stderr, "Read\n");
    }
    printf("Data read from the file..\n");
    puts(buffer);
    printf("Press ENTER to release the lock\n");
    getchar();

    fvar.l_type = F_UNLCK;
    fvar.l_whence = SEEK_SET;
    fvar.l_start = 0;
    fvar.l_len = 0;

    if ((fcntl(fd, F_UNLCK, &fvar)) == -1)
    {
        fprintf(stderr, "fcntl\n");
        return -1;
    }
    printf("unlocked\n");
    close(fd);

    return 0;
}