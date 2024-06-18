#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void childProcess()
{
    char *filename = "testfile.txt";

    if (access(filename, R_OK) == 0)
    {
        printf("Child process (PID: %d): Read access to %s is allowed.\n", getpid(), filename);
    }
    else
    {
        printf("Child process (PID: %d): Read access to %s is denied.\n", getpid(), filename);
    }

    if (access(filename, W_OK) == 0)
    {
        printf("Child process (PID: %d): Write access to %s is allowed.\n", getpid(), filename);
    }
    else
    {
        printf("Child process (PID: %d): Write access to %s is denied.\n", getpid(), filename);
    }

    exit(0);
}

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Child process created with PID: %d, Parent PID: %d\n", getpid(), getppid());
        childProcess();
    }
    else
    {
        printf("Parent process PID: %d\n", getpid());

        wait(NULL);

        printf("Child process with PID: %d has exited.\n", pid);
    }

    return 0;
}
