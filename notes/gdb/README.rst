How to use the debugger
=======================

There is a debugger on the server called ``gdb`` which you can use to find
where segmentation faults occur.  First you will need to copmile your program
with the ``-g`` flag to include symbol information:

::

  g++ progname.cpp -g -o progname

Then, run the program through ``gdb``:

::

  gdb ./progname

This will start the debugger, like so:

::

  > gdb -q ./progname
  (gdb) 

From here, you will get a ``(gdb)`` prompt. Use the ``help`` command for a list
of commands. To actually run the program, type in ``run`` followed by a list of
arguments (if there are any).  


::

  > gdb ./a.out
   ...
  (gdb) run
   ...


Segmentation faults
-------------------

Remember: segmentation faults happen because the program is trying to access
memory locations that have not been allocated! If you get segfaults, check to
make sure that:

  1. You have allocated the memory you are trying to access

  2. If the allocated memory is an array, that your indices are in range

  3. If you are using pointers, that they point to memory locations that have
     been allocated

If you run the program through gdb, it will tell where the segmentation fault
occurs (what function and line). You can then use the command ``bt`` (short for
backtrace) to get the function stack, which will tell you exactly where in the
program's execution the segmentation fault occurred.

::

  (gdb) bt


Examining code
--------------

You can use the ``disassemble`` or ``disas`` command to examine the
instructions which are being executed.  An arrow points indicates the current
instruction (and where the instruction pointer is pointing).

::

  (gdb) disas

If you compiled the code with the ``-g`` flag, you can use  

::

  (gdb) list

to find out which line is being executed.

::

  (gdb) disas

Also, it is possible to examine the registers using

::

  (gdb) info reg

and examine specific contents of the registers using ``x``; for example 

::

  (gdb) x/s $rax

would examine a string contained at the location pointed to by the register
``rax``.



Calling functions
-----------------

You can also use gdb to call functions, even if it is not possible for them to
be called in the ordinary course of program execution.  For example:

::

  (gdb) call inc(10)

would call a function ``inc``, passing it an argument of 10.  You first have to
run the program, but if you set a breakpoint at main:

::

  (gdb) break main 

then run, you can call the function as you please.


Moving and jumping
------------------

You can move to the next instruction with the ``ni`` command, which steps
over function calls as well (the function is called, returns, then the
instruction pointer moves forward).  The command ``si`` will do the same,
but descend into functions.  You can supply integer arguments to these,
so ``ni 5`` will move forward 5 instructions.

You can also use the ``jump`` or ``j`` command to jump to another instruction,
for example:

::

  (gdb) jump *0x0484e89f

will jump to the instruction at that address. It is possible to jump forward as
well as backward. You can also make relative jumps:

::

  (gdb) j *main+4

will jump to the function ``main`` at the 4th byte.


Other Utilities
===============


xxd
---

The ``xxd`` utility gives a hexidecimal dump of an object file alongside the
ASCII representation for each byte.  It also has a ``-b`` flag for printing
in binary.


strings
-------

The ``strings`` utility will give string data stored in an object file.
This can be useful if you are gathering messages output by the program,
or if you are scanning for plain-text passwords.


objdump
-------

The ``objdump`` utility, if used with the ``-d`` flag (disassemble), will give
a breakdown of the machine code.  It gives hex codes for the instructions
alongside the assembly.  It can be useful for extracting machine code, for
whatever purpose--machine code which is obtained in this way can be run on the
same architecture if it is manually loaded into memory and executed.

If you know a bit of C, you can derive assembly this way.  This is a very nice
way to learn assembly and assist in the writing of assembly programs. 


hexedit
-------

The hex editor can be used to change the values of certain bytes.  You can use
this to edit/hack executables and object files.
