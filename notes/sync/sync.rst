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


Deadlocks
---------

**Starvation** occurs when one or more processes is denied access to resources
and cannot proceed with its task.

A **deadlock** occurs when release from a waiting queue can only occur by other
waiting processes with the same characteristic.  It is the most severe form of
starvation since all processes are affected.

In the simplest deadlock scenario, suppose P0 calls wait(S) and P1 calls
wait(Q) at the same time, such that each process must wait for the other to
signal.  P1 would later invoke signal(S) and P0 would invoke signal(Q), but
since each process must wait for the other to signal, they become deadlocked.


Priority inversion
------------------

**Priority inversion** occurs when threads execute out of the intended order
according to priorities placed on them.

Suppose we have low-priority thread L, medium-priority M, and high-priority H,
which share a resource R.

Suppose L is released and executes immediately. Shortly after it starts, it
acquires a lock on resource R. Then, thread H is released and preempts thread
L. Then M is released but doesn't execute because higher-priority thread H is
still executing. Shortly afterward, thread H attempts to acquire a lock on
resource R, but cannot since thread L (a lower priority thread) still owns it.
This allows thread M to execute in place of H, violating priority.

A solution is **priority-inheritance protocol**, in which all processes which
access resources needed by higher-priority processes inherit higher priority
until they are finished with the resource.

Suppose in the example above that L had inherited the priority of H when it
acquired the lock on R.  In this case, it would not be preempted by M due to
its (temporary) higher priority.  Intuitively this makes sense; processes or
threads which need resources for which access must be limited should be given
higher priority, so that they may turn those resources over to other threads
which require them.

Synchronization Problems
========================


Bounded-Buffer
--------------

Suppose we have semaphores:

..code:: cpp

  int n;
  semaphore mutex = 1;
  semaphore full  = 0;
  semaphore empty = n;


Here, the ``mutex`` semaphore is used for mutual exclusion for access to a
buffer. ``empty`` and ``full`` count the number of empty and full buffers.
``n`` is the number of buffers.


.. code:: cpp

   do {
     // produce item
     wait(empty);
     wait(mutex);
     //add next-produced to buffer
     signal(mutex);
     signal(full);
   } while (true);


This code reads like so.  "Wait until a buffer is empty. Then wait until I can
access the buffers.  Add a produced item to the buffer.  Signal that other
processes can access the buffers now.  Signal that the buffer has been filled
with an item."


.. code:: cpp

   do {
     // produce item
     wait(full);
     wait(mutex);
     //add next-produced to buffer
     signal(mutex);
     signal(empty);
   } while (true);


This code reads like so.  "Wait until a buffer is filled. Then wait until I can
access the buffers.  Take a produced item from the buffer.  Signal that other
processes can access the buffers now.  Signal that the buffer has been emptied
by one item."


Readers-Writers
---------------

Generally, consider a database shared among multiple concurrent processes.
Some may want to read; others may write (modify or add).  There is no problem
if multiple processes read the data, but problems arise on multiple concurrent
writes, or concurrent writes and reads.  It is possible on write/write that two
processes partially write segments of the data, resulting in false values;
similarly for write/read, a false value may be read.  We want for these
combinations of operations to be mutually exclusive.

*First readers-writers problem* requires that no reader should be kept waiting
unless a writer has a lock on the data.  The *second readers-writers problem*
requires that once a writer is ready, it should perform its operation as
quickly as possible. 

A solution to either problem may result in starvation.  In the first case,
writers may starve. In the second case, readers may starve. These happen
because of the relative priority of reads and writes; if one happens quickly
enough, the other is left to wait indefinitely.

Suppose we have the semaphores:


.. code:: cpp

   semaphore rw_mutex = 1;
   semaphore mutex    = 1;
   int read_count     = 0;


``rw_mutex`` is to ensure mutual exclusion of reads and writes. ``read_count``
is the number of processes which are currently reading. ``mutex`` is to ensure
mutual exclusion when ``read_count`` is updated.

Then the writer may be as follows:

.. code:: cpp

   do {
     wait(rw_mutex);
     // write occurs
     signal(rw_mutex);
   } while(true);


That is to say, it waits until read/write mutual exclusion is guaranteed, then
writes and signals for other processes that reading and writing may continue.
As for the reader:

.. code:: cpp

   do {
     wait(mutex);
     read_count++;
     if (read_count==1)
       wait(rw_mutex);
     signal(mutex);
     //read
     wait(mutex);
     read_count--;
     if (read_count==0)
       signal(rw_mutex);
     signal(mutex);
   } while(true);


That is, it allows for writes only if there are no other readers (as per
``wait(rw_mutex)`` if read_count is newly incremented to 1, and
``signal(rw_mutex)`` if decremented to 0).  Note that there is no mutual
exclusion required for the read itself. 

Some systems have a **reader-writer** lock, which has a specific flag
to indicate whether reading or writing is to be done on a resource.


Dining-Philosophers
-------------------

Five philosophers sit at a table and only think and eat (from a bowl of rice,
at the center).  When thinking, the philosophers do not interact with each
other.  Between each philosopher is a single chopstick.  When a philosopher
becomes hungry, she picks up the left and right chopsticks and eats from the
bowl of rice until satiated.  A philosopher may pick up only one chopstick at a
time, and if a neighbor has a chopstick, she must wait until it is released
(the neighbor is finished eating).

The dining-philosophers problem represents a class of concurrency-control
problems.  A solution to representing the philosophers' behavior is to
represent each chopstick with a semaphore:


.. code:: cpp

   semaphore chopstick[5];

   do {
     wait(chopstick[i]);
     wait(chopstick[(i+1) % 5]);
     // eat
     signal(chopstick[i]);
     signal(chopstick[(i+1) % 5]);
     // think
   } while (true);


That is, each philosopher waits for the left (``i``) and right (``(i+1)%5``)
chopsticks.  Once acquired, she eats.  When finished, she lays down the
chopsticks, then resumes thinking.

A deadlock may arise if all philosophers become hungry at once and proceed to
pick up their left chopsticks.  Then they will wait indefinitely for the right
chopstick, thus resulting in deadlock (which is a form of *starvation*).

Solutions:

  * Allow only four philosophers to dine at once.
  * Pick up the chopsticks only if both available.
  * Asymmetry; odd-numbered picks up left first. 


Monitors
--------

TBD.
