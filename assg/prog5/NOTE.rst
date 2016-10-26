About Signals
=============

There are very few programming applications for CPU scheduling that do not
involve creating and inserting kernel modules.  Aside from being too low-level
to be pragmatic, such problems would require administrative privileges on my
server.  Instead I've decided to assign programming problems using signals,
which is a topic we skipped over in Chapter 4.  Since I am assigning homework
on them, I will include some test questions for them.

Signals are an important IPC mechanism used to handle common program behaviors.
SIGINT (interrupt from keyboard) is fired by a Ctrl-C, for example.  A
programmer can write a handler function which can intercept a SIGINT and
control the program behavior from there; for example, it is possible to prevent
termination even if the user enters Ctrl-C.  Processes can both send (via
``kill(2)``) and intercept (via ``signal(2)`` and a handler function) signals,
so it is possible for one process to send SIGINT to another to terminate it.
Others include SIGSEGV for segmentation faults, and SIGTERM and SIGKILL for
program termination.  As you will see, these have a wide variety of
applications.

Read the manual pages ``signal(7)``, ``signal(2)``, ``raise(2)``, ``kill(2)``,
and ``alarm(2)`` before proceeding.  Also, take a look at the codes provided
in ``src/`` for some example applications.

