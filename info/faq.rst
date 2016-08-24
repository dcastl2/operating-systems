Q: **Where should our homework directories (prog1b, prog1a, etc.) be placed?**

A: In your home directory (that is, the directory you are in upon logging in).



Q: **What should we name the executables?**

A: Anything you wish; but for your sake, it is best to name them after the
source, but without the .cpp extension. This way you can easily keep track of
what executable goes with what source code.

I do not check your executables; rather I compile your source code myself.
(Otherwise it would be easy for someone to trick me into executing a virus.)



Q: **I get a "command not found" error when I try to run a program.** If I
compile it like so:

     g++ hello.cpp -o hello

Then try running it with

     hello

it doesn't work!

A: In fact, on the server you have to run it like so:

     ./hello

The . stands for the current directory. Since hello is in the current
directory, the shell then knows to execute the executable hello in the current
directory (rather than some executable elsewhere on the system).

You can exeucte programs by name (without ./) if you add the current directory
(.) to what is called the PATH environment variable. The method for doing this
is touched upon at some point.



Q: **For the purpose of meeting line length requirements, do blank lines count?**

A: Unless otherwise specified, neither blank lines nor lone braces count for
the purpose of determining line length.

If it is specified that a program shall fit on a *page*, this means that the
total code, including blank lines and lines with lone braces, should occupy no
more than 63 lines, and no line should be more than 80 columns in length.  In
this case you may use the ``nl`` command to determine the line count:

  nl -b a file.cpp

In general, a code should have no more than one statement per line. In the
spirit of meeting the line requirements, aim to make the code as concise as
possible without compromising legibility.
