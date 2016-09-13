Processes
~~~~~~~~~


Process Concept
===============


  * A **process** is a program in execution.

  * A program is a passive entity, but processes are active.

  * The term **job** usually refers to a task run in a batch
    system.

    + Many HPC systems do batch processing. A user submits
      a job in the form of a script detailing what is to
      be done, and the system queues the job for execution
      when resources are available.


The Process Itself
------------------

  * Process information is stored in memory. 

    ::

        max ------------------
            |     stack      |
            |----------------|
            |       |        |
            |       v        |
            |                |
            |       ^        |
            |       |        |
            |----------------|
            |      heap      |
            |----------------|
            |      data      |
            |----------------|
            |      text      |
        0   ------------------


  * Note there is a maximum amount of memory allocated to the process.
    (Why?)

  * In the above diagram, **text** refers to the program code, which is
    stored on the low-end of the process; but this is often only a fraction
    of the total information stored. 

  * The **data** refers to global variables which are used by the process.

  * The **heap** has memory allocated by the process. Whenever you make
    a call to a function such as ``malloc``, the pointer to the top of
    the heap moves up.

  * The **stack** has temporary data, like function parameters, return
    addresses, local variables. 


Java Virtual Machine
--------------------

  * A process can provide a space in memory for the execution of other
    processes. This is the concept that allows virtual machines to work.

  * The Java virtual machine (JVM) is one such example. When you run
    a Java code, the JVM runs, allocating memory for the Java program
    to run inside of.


Process States
--------------

  * *New* processes are those just created. Once they are *admitted*,
    they are in a ready state.

  * *Ready* processes are ready to run. Once the CPU scheduler dispatches
    them, they are in a running state.

  * *Running* processes run until exit or termination, in which they
    reach a terminated state.  If interrupted, they will wait.

  * *Waiting* processes wait for the CPU to finish handling interrupts
    before resuming the process. After waiting a process goes back into
    a ready state.

  * *Terminated* processes may still have data left in memory even though
    they are no longer running in case of IPC needs.  


Process Control Block
---------------------

  * The **process control block** (PCB) holds information about the
    process:

    + state
    + number
    + program counter
    + registers
    + memory limits
    + open files
 

Threads
-------

  * A **thread** is a thread of execution. A process can have multiple
    threads.

  * The PCB is expanded to include information about each thread.


Process Scheduling
==================


Scheduling Queues
-----------------

  .. To be discussed

  * **Job queue**: all processes.
  * **Ready queue**: list of ready processes.
  * **Device queue**: list of processes waiting for device.
  * **Queueing diagram** shows how scheduling works.

  * Process from ready queue which undergoes execution is **dispatched**.
    Once dispatched, it may change state for different reasons:

    + An I/O request
    + Create child process and wait
    + Forcible removal (kill, SIGSTOP)

  * When the former two happen, process goes from running -> waiting -> ready
    -> running.

  
Schedulers
----------

  * A **long-term** scheduler is also called a job scheduler. Takes processes
    from disk and loads them to memory.

  * The **short-term** scheduler is also called the CPU scheduler. Takes
    processes from memory (the ready queue) and executes them.

  * Sometimes there is a **medium-term** scheduler that **swaps** out processes
    which are running to reduce the **degree of multiprogramming**.

  * Job scheduler must be careful.  To balance the system, a good mix of
    **I/O bound** and **CPU bound** processes is required.


Context Switching
-----------------

  * If an interrupt occurs, the **context** of the process must be saved 
    before handling the interrupt.

  * A **state save** is done when the process changes to waiting state,
    then a **state restore** when transiting from ready to executing.

  * This is called **context switching**.

  * Context switching is pure overhead.


Operations on Processes 
=======================


Process Creation
----------------

  * Processes are organized in a tree. When a process creates another, the new
    process is represented as a child node of the process.  Hence processes 
    that create others are called **parent processes** and the processes they
    create are called **child processes**.

  * Every process has a PID (process ID). Also stored in the PCB is the PPID
    (parent process ID).  Sometimes a child may need to have the PPID to 
    communicate with the parent.

  * When a parent creates a child, it might:

    + execute concurrently with the child, or
    + wait until the child has finished.

  * When a user enters a command on the command interpreter, the interpreter
    forks, creating a child process to handle the command while the parent
    waits. This is why terminals are unresponsive while long commands are
    executing.

    + It is possible to fork a process in BaSH by appending the ampersand
      character (&) to the command. In this case, the child process will run in
      the background while the parent (the shell) accepts commands in the
      foreground.

  * Insofar as memory is concerned, when a parent creates a child it might:
  
    + have a segment in memory which is a duplicate of the parent process, or
    + have a new program loaded into it (via e.g. ``exit()``).


Process Termination
-------------------

  * A parent may have need to terminate a child:
  
    + if the child has exceeded allocated usage.
    + if task assigned to the child is no longer needed.
    + if the parent exits.

  * The latter situation may lead to **cascading termination**; in some OS
    designs, children are not allowed to exist if the parents have terminated, so
    all process on the parent's subtree are terminated.

  * If a child process has exited, but its parent has not called ``wait()``, then
    the child is known as a **zombie** process, but only until the parent calls
    ``wait()``.

  * If the parent exits and the OS design permits the child to stay alive, then
    the child process then becomes an **orphan**.

  * ``init()`` regularly collects orphan processes by calling ``wait()``.


Interprocess Communication
==========================

  * IPC may be for several reasons:

    + information sharing among users
    + speed increases for parallel jobs
    + modularity of design
    + the convenience of time-sharing

  * Two main IPC mechanisms are **shared memory** and **message passing**.

  * There are also **sockets** and **pipes**.


Shared-Memory Systems
---------------------

  * A producer process creates a message or some form of data or information
    which it writes to a shared memory object.

  * A consumer process reads the data from the shared memory object.

  * Both the consumer and producer use a name on the memory segment which they
    each may use to refer to it.

  * Buffers can unbounded or bounded (size limit).

  * In POSIX (portable operating system interface) systems, shared memory can
    be opened using the ``shm_open`` system call.


Message-Passing Systems
-----------------------

  * Message passing involves sending information to a receiver. Refers to the
    logical implementation.  Physically it may be enabled via shared memory,
    hardware bus, or network. 


Naming
~~~~~~

  * Typically ``send`` and ``recv`` primitives are defined for messages. May
    use direct communication by referring to other processes by names.  P
    may send a message to Q, for example (symmetric; both processes must
    know each others' names).

  * Message-passing can be asymmetric, so that a process is allowed to receive
    messages from any other process.

  * Indirect communication is possible by sending messages to ``mailboxes``
    or ``ports`` which reside in memory.  Owners receive messages, users send.

  * Suppose P1 sends message to mailbox M, then P2 and P3 call a ``recv`` from
    M. Which one receives? Answer depends:

      + Could allow only one link at a time
      + Could allow only one ``recv`` call at a time
      + Could handle the message using an algorithm, such as **round robin**

  * Mailboxes can be owned by processes or by operating system. The operating
    system has the responsibility of enabling processes to create/delete 
    mailboxes and send/receive messages through them.


Synchronization
~~~~~~~~~~~~~~~

  * Message passing can be **blocking** or **nonblocking**, also known as
    synchronous or asynchronous.  Blocking means process waits, nonblocking means
    process does not wait--instead it resumes immediately following the
    operation.

    + Blocking send means sender blocks until receiver receives.
    + Blocking receive means receiver blocks until receiver receives.
    + Nonblocking send means sender resumes after send.
    + Nonblocking receive means receiver retrieves message or NULL.

  * If both send and receive are blocking, there exists a **rendevous** between
    sender and receiver. 

Buffering
~~~~~~~~~

  * Messages echanged reside in a queue, which can be

    + Zero capacity.  Means the sender must block.

    + Bounded capacity.  Queue has finite length.  If the queue is full,
      sender must block.

    + Unbounded capacity. Queue is never full. Sender never blocks.

  * The latter two are referred to as systems with automatic buffering.

Examples
========

  * See codes.


Client-Server Communication
===========================

  * A **socket** is a communication endpoint.  Think of an electric socket
    as being the endpoint for an electrical connection.

  * Socket is identified by an IP and a port. Ports below 1024 are well-known.

  * 127.0.0.1 is referred to as **loopback**; this is the machine's own
    address.

  * TCP (transmission control protocol) sockets are connection-oriented. 
    A connection exists between client/server and information is sent via
    a stream. It is more complex and slower but more reliable.

  * UDP (universal datagram protocol) sockets are connectionless. Information
    is sent in packets. It is lighter and faster but less reliable.

  * In POSIX, sockets can be created using the ``socket`` system call.

  * In Linux, ``netcat`` can be used to make a client/server.


Remote Procedure Calls
----------------------

Pipes
-----

  * A **pipe** is a conduit allowing two processes to communicate. In a pipe,
    there is at least one write end and one read end.  It can be unidirectional
    or bidirectional.

  * Can also be half-duplex, which means data is allowed to travel one way at
    a time, or full-duplex, which means it can travel both ways at the same time.

  * Pipes can be used to communicate between parent-child processes and over
    networks.

  * In POSIX, pipes can be created using the ``pipe`` system call.

  * In Linux, ``mkfifo`` can be used to make a pipe in the form of a file.

