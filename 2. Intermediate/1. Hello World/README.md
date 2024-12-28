# Notes

There are few things to note:

- The `<unistd.h>` provides the `write()` function.
- The file descriptor 1 (*which is the stdout*) is for the standard output. The one that is seen here:
    ```c
    write(1,message,13);
    ```
