#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int cpid1 = fork();
    int cpid2 = fork();

    if (cpid1 != 0 && cpid2 != 0)
    {
        int waitPID = 0;
        int status = 0;

        printf("Parent is waiting for child %d\n", cpid2);

        while (waitPID == 0)
        {
            waitPID = waitpid(cpid2, &status, WNOHANG);
        }

        printf("Parent waited for child: %d\n", waitPID);
        printf("Exit code of the terminated child: %d\n", WEXITSTATUS(status));

        exit(1);
    }
    else if (cpid1 == 0 && cpid2 != 0)
    {
        printf("Child1: %d\n", getpid());
        exit(1);
    }
    else if (cpid1 != 0 && cpid2 == 0)
    {
        printf("Child2: %d\n", getpid());
        exit(2);
    }
    else
    {
        printf("Child3: %d\n", getpid());
        exit(3);
    }

    return 0;
}