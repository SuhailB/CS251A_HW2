#include <stdio.h>
 
extern int func(void);
// the definition of func is written in assembly language
__asm__(".globl func\n\t"
        ".type func, @function\n\t"
        "func:\n\t"
        ".cfi_startproc\n\t"
        "movl $7, %eax\n\t"
        "ret\n\t"
        ".cfi_endproc");
 
float subtractR(float in1, float in2)
{
    float ret = 0.0;
    asm ("fsubr %2, %0" : "=&t" (ret) : "%0" (in1), "u" (in2));
    return ret;
}
float subtract(float in1, float in2)
{
    float ret = 0.0;
    asm ("fsub %2, %0" : "=&t" (ret) : "%0" (in1), "u" (in2));
    return ret;
}
int main(void)
{
    int n = func();
    // gcc's extended inline assembly
    __asm__ ("leal (%0,%0,4),%0"
           : "=r" (n)
           : "0" (n));
    float x1 = subtract(2,5);
    float x2 = subtractR(2,5);
    printf("%f\n%f\n", x1, x2);
    fflush(stdout); // flush is intentional
 
    // standard inline assembly in C++
    __asm__ ("movq $60, %rax\n\t" // the exit syscall number on Linux
             "movq $2,  %rdi\n\t" // this program returns 2
             "syscall");
}