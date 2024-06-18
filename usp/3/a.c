#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    const char *command = "ls";

    if (command == NULL)
    {
        fprintf(stderr, "Command is NULL\n");
        exit(-1);
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        fprintf(stderr, "Fork failed\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            fprintf(stderr, "Wait Pid failed\n");
            exit(-1);
        }
        else
        {
            printf("Command executed with exit status : %d\n", WEXITSTATUS(status));
            return status;
        }
    }

    return 0;
}