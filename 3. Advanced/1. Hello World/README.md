# Two Files

The goal here was to print the message, without using libraries like in `beginner` and `intermediate` levels.

## x86-64

I used the inline assembly for the directly system calls

```c
asm(
    "mov $1, %%rax\n" /* systemcall for the write(1) */
    "mov $1, %%rdi\n" /* file descriptor for stdout */
    "mov %0, %%rsi\n" /* pointer to the message */
    "mov $13, %%rdx\n" /* length of the message */
    "syscall\n"
    // ....
);
```

## Very Low Level, DOS

For the old systems like MS-DOC, we can use the interrupt calls directly. As seen from the file `int 0x21` is the interrupt for printing a string. And also the string must end with `$` instead of a null terminator.

### Final Note:

Why going this far?, Next time just import `<stdio.h>` haha!.
