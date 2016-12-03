Homework 6
==========

Select up to 64 points worth of problems.  You may earn +N extra credit points
if you submit the assignment N<=8 days in advance of the due date (Sunday at
6:00:00 PM on 11/27/2016).


0. Virtual address space translation.
     [32] Write a program which accepts either one or two command-line
     arguments, and outputs different quantities depending on the number
     of command-line arguments:
     
       * if one argument is passed, it is assumed to be a hex address; then
       assuming 32-bit architecture, prints the page number and offset for the
       byte at that address. 

       * if two arguments are passed, it is assumed to be the page number and
       offset; and returns the virtual address.

     These are command-line arguments; hence they should be accepted when
     invoking the program program (look in ``argv`` for them).  Input hex
     addresses are formatted with a leading ``0x`` like so: ``0x42D2``. Assume
     the page size is 4K.  Call this ``virtual.c``.


1. Rust, the up-and-coming systems programming language.
     [32] Write a program in Rust which accepts via stdin any number of shell
     commands, line-delimited, until the user enters ``quit``.  It should then
     create an equal number of threads, each of which shall run a command from
     the list.  The output of each command should be given if and when the
     command successfully finishes.  Call this ``parashell.rs``.

     Rust is compiled with the ``rustc`` compiler, which is installed on the
     system.  Look at sections 18.1 and 18.5 of the Rust language tutorial for
     information on how to create threads and child processes.  


2. Buffer overflow attacks.
     [32] I have included a source for ``meow``, which accepts a string using
     the dated ``gets`` function which is susceptible to buffer overflow
     attacks because it does not constrain the size of its input.  Ultimately,
     this opens up the opportunity for an attacker to overwrite the return
     address of the callee function's stack frame, causing control flow to jump
     wherever the user desires.  The ideal location would be somewhere earlier
     or later in the attack string, so that the attacker's own code may be
     executed.

     Use ``gdb``, ``objdump``, ``gcc`` and the program ``hex2raw`` to construct
     an exploit string which spawns a shell (use ``/bin/sh`` so you can tell
     the difference when the shell spawns) using the ``system`` function when
     it is entered to ``meow``.  Place the hex code into an exploit file called
     ``exploit.txt``.  If successful, your exploit string will give you a
     shell.  You may find this resource interesting: 
     
       http://insecure.org/stf/smashstack.html


3. Implementing ``malloc``.
     [64] Using the ``brk`` (stands for "break") and/or ``sbrk`` system calls,
     write your own versions of ``void *malloc(size_t s)`` and ``void free(void
     *ptr)``.  You can implement ``malloc`` using a linked list.  Each node of
     the list should contain the size of the allocated block, a pointer to the
     next block, and a boolean flag indicating if the block is free (i.e., a
     hole).  ``free`` should simply mark the free flag as true.  Note that the
     pointer you return should be at the start of the allocated memory; thus it
     is a few bytes ahead of your metadata.

     Your ``malloc`` should look to see if there are any holes to be filled
     before incrementing the heap pointer.  If there are any holes larger than
     the memory requested, it should split the given hole into two pieces,
     allocate memory in one, and link them in the list.  Use the first fit
     algorithm for finding fits.  Make sure to account for the size of your
     metadata for the purpose of determining fitness.

