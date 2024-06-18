#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

void second(void)
{
    printf("In second function\n");
    longjmp(buf, 1); // Jump back to where setjmp was called
}

void first(void)
{
    register int reg_var = 10;
    volatile int vol_var = 20;

    printf("In first function\n");
    printf("Before longjmp: reg_var = %d, vol_var = %d\n", reg_var, vol_var);

    if (setjmp(buf) == 0)
    {
        reg_var = 30;
        vol_var = 40;
        second();
    }
    else
    {
        // Note: The value of reg_var may be unexpected after longjmp
        printf("After longjmp: reg_var = %d, vol_var = %d\n", reg_var, vol_var);
    }
}

int main(void)
{
    first();
    return 0;
}
