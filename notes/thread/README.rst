Threads
=======

A **thread** refers to a thread of execution.  Threads belong to a process.
Threads share process code, data, heap, and any files (as per those opened in
the file descriptor table). Threads have their own stack and registers,
however.

A multi-threaded application might be a web server, which should handle
requests concurrently if possible. For each request that is made, a new thread
is created which will handle the request.


Benefits of multi-threading
---------------------------

  * Responsiveness. Applications are responsive to user input in a
  multi-threaded environment.

  * Resource sharing. Threads automatically share memory and resources of the
  process they belong to.

  * Economy. Process creation is slower than thread creation.

  * Scalability. Well-written multi-threaded codes can scale in multi-processor
  architectures with a greater number of processors.


Multicore programming
=====================

Refers to programming to utilize multiple cores in a system.

**Parallelism** is running one task on multiple cores or processors. A single
program to calculate pi may run in parallel.

**Concurrency** is running multiple tasks on multiple cores or processors. A
web browser may run concurrently with a word processor.


Challenges of multi-threaded programming
----------------------------------------

  * Task identification
  * Load balancing
  * Splitting data
  * Calculating dependencies
  * Testing and debugging

Types of Parallelism
--------------------

  * **Data parallelism** involves splitting data among multiple cores and 
  processing each independently. An example is summing 1 to n; we can sum
  1 to n/2 on one core, then n/2+1 to n on another.  Finally, add them.

  * **Task parallelism** involves splitting work among multiple cores.  Each
  task might have read access to the same data and perform a different task;
  one thread may calculate an average of an integer array while another finds
  the median.


Multi-threading models
======================

There exist **user threads** and **kernel threads**, which run in user space
and kernel space.  There are three different models as to how these are
mapped:

  * **Many-to-one**: many user threads execute; however if a thread makes a
  blocking system call, the whole process stops to wait for a kernel thread to
  handle it.

  * **One-to-one**: each user thread has a corresponding kernel thread.  If the
  user thread makes a blocking system call, only the corresponding kernel
  thread will handle it and only that user thread will wait.

  * **Many-to-many**: user threads are multiplexed to kernel threads.  Since
  creating kernel threads can blow up kernel space memory, only a few threads
  are created and used to handle blocking system calls.


Thread libraries
================

**Pthreads** stands for POSIX thread standard. It is a specification, not an
implementation.  We will look at the C library implementation, *pthreads*.
