# cc command

In simple terms the `cc` works in these phrases `preprocessing`, `compilation`, `assembly` and `linking`. To see it in work you can type this to the `hello_world.c`.
    ```bash
    cc -v hello_world.c
    ```
Then you will see the output of this phrases as the file was processed. As first from some books they said with capital `-V` that didn't work out haha!.

## Under The Hood

Often the cc is often a symbolic to `gcc`, and sometimes it may point to `clang`. You can see for yourself on your machine:
    ```bash
    ls -l /usr/bin/cc
    ```

## Compilation

So now there are another two files `hello_main.c` and 'hello.c', the `hello_main.c` is the file that is calling the function that has been defined on the `hello.c` which is called `print_from_another_file()`. And here is something I learnt here before going too far:

- On both two files, there is a header `#include<stdio.h>`, which is strange as the only file that is using that header is the `hello.c`, while the `hello_main.c` is just using that function. It turns out that it is neccessary to include that `include..` in both files as `C compiler` processes each resource file independently during the compilation phrase. And more explations *The compiler does not automatically see or inherit headers included in another resource files unless explicitly told through headers or linking`.
- Another adds on, In older C standards(ie C89), the compiler might assume the printf returns an `int` and takes an unspecified number of arguments, which can lead to undefined behaviour.

Let's continue on *compilation*, when we run the `hello_main.c`:

```bash
cc hello_main.c
```

The compiler will generate an error, because the linker cannot find the definition of the function. As by default `cc` compiles the links files in one step.Since `hello_world.c` is not included, the linker cannot resolve the symbol `print_from_another_file()`.

So, we'll provide additional informations during compilation and linking:

```bash
cc hello_main.c hello.c -o hello_world.out
```

There we included both files in the `cc` command, the compiler will compile both files and the linker will resolve the symbol `print_from_another_file()`.

## Advanced

We can use object files:

```bash
cc -c hello.c
```

Then compiling the `hello_main.c` and linking it with `hello.o`:

```bash
cc hello_main.c hello.o -o hello_world.out
```

So, it's like using `-c` allows you to compile files separately before linking them together.
