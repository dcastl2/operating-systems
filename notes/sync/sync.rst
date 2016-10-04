Process Synchronization
=======================

An Example of a Race Condition
------------------------------

Following is an example of a producer-consumer system which can result in
unintended consequences.  In this example, items are produced by the producer
process indefinitely.  A counter is used to maintain how many items are in the
buffer. Each time the producer process produces an item, the counter is
incremented; each time the consumer process consumes an item, the counter is
decremented.  The ``counter`` variable is global.

If in the producer process the counter equals the buffer size, the buffer is
full and the producer must wait until the consumer consumes an item; then it is
free to fill the buffer with another.  Likewise if in the consume process the
counter is zero, there are no items to be consumed, so the consumer must wait
until the producer process produces an item to be consumed.

The index ``in`` represents the location in the buffer where the item is to be
produced next, and ``out`` represents where in the buffer the next item is to
be consumed.  These are incremented for each production and consumption,
respectively, and are rounded to zero when they exceed the buffer size.


Producer process:


  .. code:: cpp

     while (true) {
       // produce item
       while (counter == BUFFER_SIZE);
       buffer[in] = item;
       in = (in + 1) % BUFFER_SIZE;
       counter++;
     }


Consumer process:


  .. code:: cpp

     while (true) {
       while (counter == 0);
       item = buffer[out];
       out = (out + 1) % BUFFER_SIZE;
       counter--;
       // consume item
     }


If executed separately, there is no issue; however if these processes are
executed concurrently, there is a risk that the counter will not reflect
the intended value because of the way registers work. To increment the
counter in the producer process, the following machine language may be
used:

  .. raw::

     r1      = counter
     r1      = r1 + 1
     counter = r1

For the consumer process:

  .. raw::

     r2      = counter
     r2      = r2 - 1
     counter = r2


Suppose ``counter`` has value ``n``, and then one iteration of the producer
loop is executed followed by one iteration of the consumer loop. This results
in a final value of ``n`` for ``counter``.  However, if executed concurrently,
it is possible for these machine language instructions to be spliced in such a
way as to give a false value for counter:


  .. raw::
     
     r1      = counter
     r1      = r1 + 1
     r2      = counter
     r2      = r2 - 1
     counter = r1
     counter = r2


Suppose ``counter`` has value ``n`` initially; then by end-of-execution it
will have value ``n-1``, which is false!

Such a situation, in which the output or final result is dependent upon the
order of execution of statements, is called a **race condition**. 


The Critical-Section Problem
----------------------------

In such codes which may cause a race condition, the "sensitive" portion of the
code is called a **critical section**. This is the section which is responsible
for updating global variables, shared memory, writing to files, or any other
data which is shared by multiple processes.

Consider processes {*P1*, *P2*, ..., *Pi*, ... *Pn*}, each of which execute the
same code with the same critical section (which updates some shared data).  To
prevent race conditions, we desire that when the process *Pi* executes its
critical section, no other process in {*P1*, *P2*, ..., *Pn*} may execute its
critical section.  The problem of designing a protocol in which processes may
cooperate so, is called the **critical-section problem**.

The typical layout of such code is:


  .. code:: cpp

     do {
        // entry section
        // critical section
        // exit section
        // remainder section
     } while (true);


A solution to this problem must satisfy three requirements:

  1. **Mutual exclusion**. If *Pi* is executing its critical section, no other
  process may execute its critical section.

  2. **Progress**. If no process is executing its critical section, only those
  processes which are not executing their remainder section may decide which
  shall next execute its critical section; and this selection cannot stall the
  execution.

  3. **Bounded waiting**. There is a limit on the number of times other
  processes are allowed to enter their critical sections after a process has
  made a request to enter its critical section and before the request is
  granted (no bullying).


Kernel data structures such as the list of open files are subject to race
conditions.  To handle critical sections in operating systems, two types of
approaches are available: preemptive kernels and nonpreemptive kernels.  A
**preemptive** kernel allows process to be preempted while in kernel mode; a
**nonpreemptive** kernel does not.

Nonpreemptive kernels are free from race conditions since only one kernel
process is active at a time (barring threads). Preemptive kernels are more
responsive, but must be designed carefully to avoid race conditions.  


Peterson's Solution
-------------------

**Peterson's solution** is a classic solution to the critical-section problem.
It is restricted to two processes, *Pi* and *Pj*.  The solution requires two
globals: ``int turn``, which indicates whose turn it is to enter the critical
section; and ``boolean flag[2]``, in which each process indicates its readiness
to enter its critical section.  The general layout of the code of each process
is as follows:


  .. code:: cpp

     do {

        flag[i] = true;
        turn    = j;
        while (flag[j] && turn == j);

        // critical section

        flag[i] = false;

        // remainder section

     } while (true);


The statement ``flag[i] = true`` indicates that process *Pi* is ready to enter
its critical section.  This flag is unset after *Pi* finishes executing its
critical section.  *Pi* sets ``turn = j`` to indicate that if *Pj* wishes to
enter its critical section now, it may.  Then the condition ``flag[j] && turn
== j`` is true so long as it is *Pj*'s turn (that is, so long as *Pj* is
executing its critical section). 

If false, the condition ``flag[j] && turn == j`` implies that one of two things
must be true: either ``flag[j]`` is false, indicating that *Pj* is executing
its remainder section, or else *Pj* is ready but has indicated that if *Pi*
wishes to execute its critical section now, it may.

This satisfies the three requirements (mutual exclusion, progress, bounded
waiting).

Mutual exclusion is satisfied because the condition ``flag[j] && turn == j``
must be true for one process, but not the other, if both are attempting to
execute their critical section.  The value of ``turn`` must be either ``i`` or
``j``; and if both processes are attempting to execute the loop, then ``flag[i]
== true`` and ``flag[j] == true`` because they are set by a previous statement. 

Progress is satisfied because the condition ``flag[j] && turn == j`` is the
only which can stall the progress, and it is guaranteed to have one process or
the other executing.  In case the condition is true, it implies that *Pj* is
executing its critical section.  Once finished, *Pj* will set ``flag[j] =
false`` (note the above code is for *Pi*, so in *Pj*'s version the indices
are switched), thus falsifying the condition and allowing *Pi* to run.

Thus after at most one loop by *Pj*, *Pi* will be allowed to execute its
critical section, satifying the bounded waiting requirement.


Synchronization Hardware
------------------------

Most software synchronization solutions rely on **locking**: protecting
critical regions through the use of software locks.  Peterson's solution relies
on a lock of sorts via the ``turn`` and ``flag`` variables.  Modern computer
systems enable the testig and manipulation of data ``atomically``, that is, as
an uninterruptible unit.  

The following function may lock a bit (set it to true), and return its previous
value to tell if it had been locked before. It is called the **test-and-set**
instruction.


  .. code:: cpp

     bool test_and_set(bool *target) {
       boolean locked = *target;
       *target = true;
       return locked;
     }


This may be utilized so:


  .. code:: cpp

     do {
       while (test_and_set(&lock));
       // critical section
       lock = false;
       // remainder section
     } while (true);
     

A necessary characteristic of the test-and-set operation is that it is executed
atomically.  If two test-and-set operations are to be performed, they should be
executed sequentially in arbitrary order, rather than concurrently.

Also there exists a **compare-and-swap** instruction supporting a locking-based
solution to the critical-section problem:


  .. code:: cpp

     bool compare_and_swap(int *value, int expected, int new_value) {
       int temp = *value;
       if (*value == expected)
           *value =  new_value;
       return temp;
     }


which can be used as follows:


  .. code:: cpp

     do {
        while (compare_and_swap(&lock, 0, 1) != 0);
        // critical section
        lock = 0;
        //remainder section
     } while (true);


Mutex Locks
-----------

A **mutex lock** stands for *mutual exclusion lock*; it is a software lock
which ensures mutual exclusion of execution of critical sections of processes.
The functions ``acquire()`` and ``release()`` support the use of mutex locks,
and they are defined as follows:

.. code:: cpp

   acquire() {
     while (!available);
     available = false;
   }

   release() {
     available = true;
   }


These are executed atomically.  If any process is in its critical section,
another must wait (loop, doing nothing) until the lock is released.  This is
called **busy waiting**, and since ``acquire()`` loops until the lock is
available, this type of lock is called a **spinlock**.

In a multiprogrammed uniprocessor system, spinlocks can pose an issue because
they do nothing but needlessly wait.  On multiprocessor systems this behavior
is put to better use, since one processor can wait, spinning, while the other
completes its critical section.


Semaphore
---------

A **semaphore** is an integer variable that is accessed by ``wait()`` and
``signal()`` operations.


.. code:: cpp

   wait (S) {
     while (S <= 0);
     S--;
   }

   signal (S) {
     S++;
   }

These are atomic as well.  This is an example of a **counting** semaphore.
A **binary semaphore** has possible values 0 or 1.  The advantage of using
counting semaphores is to restrict some resource to a finite number of
processes.


