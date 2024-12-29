# cc in Deep

We have seen in simple terms the phases in which the file is going through after the `cc` command. Now let's continue:


## Preprocessor
 
When we run the `preprocessor.c`, at the preprocessor phase, these things are going to be handled:
    - include directives
    - macros
    - conditional compilation

So for example our file `preprocessor.c` when we run it, we will see...

```c
........
int main(){
    printf("The value of PI: %f\n", 3.14);
    return 0;
}
```

And it generate an output file called `preprocessor.i`, as i put the `....` above `int main(){` is that the above it will be the contents of `#include<stdio.h>` being included. And as you saw it the `3.14` has been replaced to all the `PI`. You can see yourself with this command( *the preprocessor* ):

```bash
cc -E preprocessor.c
```

## Headers

So on the file `hello_world.h`, we defined our function prototype and macros. And we say the `#ifdef` which prevents double inclusion (*header guards*), and the `#define` which defined our macros, and etc..

And now when you use this command again:

```bash
cc -E hello_world.c
```

Now we can see the contents of the `hello_world.i` being displayed, and all the macros being expanded, and all the includes are being included in the `.i` file.

So sometimes, the headers may be somewhere out of your working directory, what you gonna do?. The `-I` subcommand is the help.
    ```bash
    cc hello_main.c hello.c -I . -o hello.out
    ```

From that command you are telling that the headers are here in this directory `.`, but when they are somewhere else you can specify the path. And by default the preprocessor finds the headers file in the currently directory.

# Note

The `-I` sub command is very useful, It is widely used.
