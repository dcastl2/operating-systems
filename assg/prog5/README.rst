Homework 5
==========

Select up to 64 points worth of problems.  You may earn +N extra credit points
if you submit the assignment N<=8 days in advance of the due date (Sunday at
6:00:00 PM on 11/13/2016).


1. Unstoppable processes.
     [16] Write a program code for a process which spins indefinitely.  If any
     signal intended to stop it is sent to it, it should respond by forking
     itself, thus creating a daemon child process which uses the same signal
     handlers.  Therefore call this ``demon-child.c``.

     The only signal the process cannot intercept is SIGKILL, which you can use
     to kill it.  Use ``killall -KILL demon-child`` to end it once and for all.


2. Killing everything.
     [16]. Write a program to loop from the maximum PID (defined in limits.h)
     down to 1 and send a SIGKILL kill signal to all user processes.  It should
     not kill itself (or its parent process, the terminal) before it completes
     its task.  Call this ``clean.c``.


3. Implementing sleep(3).
     [16] The function ``sleep(3)`` can be implemented using ``alarm(2)`` and
     ``signal(2)``. Implement the function ``void sleep(int seconds)`` in
     terms of these system calls.  Call the file ``sleep.c``.


4. Segmentation fault trickery.
     [16] Write a program to accept a PID as a command-line argument and send a
     SIGSEGV signal to it to indicate a segmentation fault has occurred in that
     process (the process will print out the classic "Segmentation fault"
     message on its own, as per the default signal handler).  Call this
     ``seg.c``.


5. Backtraces on segmentation fault.
     [16] Write a program which uses a signal handler for SIGSEGV to print out
     more useful information during a segmentation fault. Yours should print a
     backtrace for the process. Call this ``backtrace.c``. See the following
     URL for a function to print backtrace information:

     https://www.gnu.org/software/libc/manual/html_node/Backtraces.html


6. Virtually unstoppable self-replicating programs.
     [32] Modify ``kitties.c`` to fork before executing its replica.  This way,
     if the parent exits or is killed by SIGKILL, the child will continue to
     replicate.  Likewise prevent signals intended to stop it, as in the above
     problem.  Call this ``demon-kitties.c``.

     You must be doubly cautious with this program because any means of
     managing it are outside of your control.  Even with SIGKILL provided by
     ``kill`` or ``killall``, you must specify the PID or name of the process;
     but this is complicated by the fact that the name constantly changes.  You
     must develop and test this in your own sandbox.


7. A FCFS multi-threaded job scheduler. 
     [32] Write a program ``schedule.c`` which can open a file ``cmds.sch``
     which should contain Unix/Linux commands or programs, one per line.  These
     are not intended to be run sequentially, as in a program.  Rather, your
     scheduler will run at most four at a time, each in its own thread.  
     
     Use the ``pthread`` library.  You will also need to use a counting
     semaphore to keep track of the number of commands running at once.  You
     can use the ``popen(3)`` function for easy fork/pipe functionality.  The
     program should print a message indicating what command it is running prior
     to the run, and a message to indicate when the run is finished.
