Homework 2
==========

Select up to 64 points worth of problems.  You may earn +N extra credit points
if you submit the assignment N<=8 days in advance of the due date.


1. Echo input using system calls.
     [16] Write a program which accepts a filename as a command-line argument,
     then continuously reads a line from stdin and outputs the same line to
     stdout and to the file (as indicated by the filename).  You must use only
     system calls (no calls to ``printf`` or ``scanf`` are allowed).  You can
     ensure that you use only system calls by verifying the manual page section
     of the corresponding libc API function (e.g. ``man 2 open`` yields a
     result, so ``open`` is a system call). Call this ``echo.c``. Be sure to
     distinguish this echo from the system command ``echo``.


2. Forking processes to calculate series and products.
     [16] Write a program which accepts an integer command-line argument (call
     it ``n```).  The program should then fork.  The parent process shall
     calculate the product of numbers 1 to n, while the child process
     calculates the sum of numbers 1 to n (so they may potentially be done
     concurrently on a multiprocessor system).  The parent should wait for the
     child to finish executing before printing its result.  Call this
     ``series.c``.


3. Utilizing pipes to calculate combinations.
     [16] Write a program which can calculate *(m choose n)*, which is a count
     of the number of possible combinations of *n*-number items from a pool of
     *m*-number items. For example, the number of five-card hands possible from
     a standard 52-card deck is (52 choose 5), which is  ``(52 x 51 x 50 x 49 x
     48) / (1 x 2 x 3 x 4 x 5)``. 
      
     The program should accept m and n as command-line arguments. It should
     then fork.  The parent should calculate *m!/((m-n)!n!)*, which is a
     product of *n* numbers.  The child should calculate *n!*.  A pipe will
     then be used to transfer the result of *n!* to the parent, which will then
     complete the calculation by dividing the two results, and output the final
     result to stdout.  Call this ``choose.c``.


4. Using shared memory to exchange secret messages among users.
     [16] Write a program which opens a shared memory object named after your
     PAWS ID, then writes a personal message to the object no longer than 4096
     bytes. Your program should protect the object such that only you can write
     to it, but anyone can read it. 

     Furthermore the program should accept a PAWS ID as a command-line
     argument, then open a shared memory object named after the given PAWS ID.
     It should then print the message written to that shared memory object, if
     there is any.  Call this program ``secret.c``.


5. Systems calls used to create a self-replicating program.
     [16] More affectionately known as a *virus*; however this assignment
     only involves executables which self-replicate locally.
     
     Create a program which copies itself (the running executable) into another
     file with a random name of 8 lowercase characters.  It should then make a
     system call to ``chmod`` to modify the permissions of the copy so as to
     make it executable.  Finally it should execute it using one of the
     ``exec`` family of functions, thus propagating its replication. Name this
     ``kitties.c``. 

     You must develop this on your OWN computer, and ideally include a
     mechanism for stopping it after e.g. the 10th replication. **If you *dare*
     execute such a program on my server, you will automatically fail the
     second test.**

     Local virii are relatively harmless, unless they do some secondary task
     such as deleting files/directories.  At most, they consume all the space
     on the filesystem, thus preventing any files from being created and making
     the system temporarily unusable.  To recover, the filesystem must be
     externally mounted and the files cleaned, then the system must be
     rebooted.  If you are using a Live Linux medium you should just be able to
     reboot to recover (though you will lose the file you were working on);
     otherwise see me if you need help recovering.


6. Using sockets to write a backdoor using the client/server model.
     [32] Write a server which accepts connections from a client.  The server
     should accept commands in the form of string data from the client, execute
     them locally, then send output back to the client.  The client should
     support sending commands typed via stdin locally.  Call the server-side
     program ``pony.c`` and the client-side ``carrot.c``.  For the purpose
     of the assignment, your client/server should both operate on localhost
     (though this could easily be changed to a host of your choosing).


7. Writing code to shared memory to be executed by another process.
     [32] It was discussed in class that it is in theory possible to load code
     into shared memory to be executed by another process.  If you know about
     function pointers, you can do this.  It is not a practical use of IPC,
     though it may be possible to use it in conjunction with other mechanisms
     to attack a system, such as to get a privileged process to execute 
     arbitrary code stored in shared memory.

     The following is assembly code for a function ``int inc(int n)`` which
     accepts an integer and increments it by 1:

     :: 

       0x55, 0x48, 0x89, 0xe5, 0x89, 0x7d, 0xfc,
       0x8b, 0x45, 0xfc, 0x83, 0xc0, 0x01, 0x5d, 0xc3

     Assembly hex codes sequences such as this can be obtained by writing the
     function in C, then using a command ``objdump`` with the ``-d`` flag to
     disassemble it.

     Write a producer code called ``producer.c`` which loads this code into a
     shared memory block. Name the block after the reverse of your PAWS ID
     to avoid collisions with other students.

     Then write an executor code called ``executor.c`` which opens the shared
     memory block and calls the function (you require rudimentary knowledge of
     function pointers to do this).  To test it, pass in an integer argument
     and print out the return value to prove that the code was in fact
     executed.  Be sure to unlink the shared memory object when finished.
