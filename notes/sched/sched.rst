CPU Scheduling
==============

Basics
------

To maximize CPU utilization in a multiprogrammed environment, a process should
be running at all times.  Sometimes processes have to wait for I/O requests to
be fulfilled.  In a simple system, the CPU sits idle, but this is a waste of
resources; so in a multiprogrammed environment, we allow for another process
to use the CPU while the I/O request is handled.

Thus a process may go back and forth between **I/O bursts** and **CPU bursts**,
in cycles. I/O-bound programs typically have short CPU burst durations. The
frequency curve for CPU burst duration typically has a high relative peak at a
short duration, then tapers off quickly at longer durations.

When the CPU becomes idle, the OS must select out of the ready queue a process
to be executed. This is the responsibility of the **short-term scheduler**.
This is not necessarily a FIFO queue, as we will see.  It could be a priority
queue, tree, or unordered list.  Records in these queues are typically
contained in the PCBs of the process.

CPU-scheduling decisions take place when:

  * running -> waiting     (e.g. by wait())
  * running -> ready       (some interrupts)
  * waiting -> ready       (completion of I/O)
  * termination
  
For running->waiting and termination, there is no choice in terms of
scheduling.  A new process must be selected for execution (that is, one that is
not in the ready queue).  The schedling scheme in this case is
**nonpreemptive**. For those processes which switch into the ready state, there
is a choice; we call the scheme **preemptive** in this case.  Preemptive
scheduling can cause issues with shared data, as we have seen.

The **dispatcher** is the component which gives control of the CPU to the process
selected by the short-term scheduler. It is responsible for:

  * context switching
  * switching to user mode
  * jumping to text location

**Dispatch latency** is the amount of time it takes for these operations.


Scheduling Criteria
-------------------

When evaluating scheduling algorithms, we consider several criteria:

  * **CPU utilization**: we want for the CPU to be utilized as much as possible

  * **Throughput**: processes completed per unit time; we want this to be as
  high as possible

  * **Turnaround time**: time from submission of process to completion; sum of
  time spent in all process states

  * **Waiting time**: this is time spent in the ready queue (not the waiting
  state)

  * **Response time**: time from submission of request to first response
  produced; important for an interative system, may be better to minimize
  variance in response time than decrease mean


Algorithms
----------

FCFS
....

**First-come first-serve (FCFS)** schedules in FIFO order.  The first processes
to be put in the ready queue are the first to be dispatched.  Example:

::


    Process            Burst Time (ms)
    -------            ---------------
      P1                   24
      P2                    3
      P3                    3


We can construct what is called a **Gantt chart** for representing the process
dispatches over time.

::

  +------------------------+-----+-----+
  |           P1           |  P2 |  P3 |
  +------------------------+-----+-----+
  0                        24    27   30
  

For evaluating this algorithm, let us examine the waiting time.  To calculate
the waiting time, we average the time to wait for each process and divide by
the number of processes).  We must wait 0ms for P1, 24ms for P2, and 27ms for
P3.  Thus the average is (0+24+27)/3 = 17ms.

Had the processes been scheduled in a different order, such as the following:


::

    Process            Burst Time (ms)
    -------            ---------------
      P1                    3
      P2                    3
      P3                   24


We would have the following Gantt chart:


::

  +-----+-----+------------------------+
  | P1  | P2  |          P3            |
  +-----+-----+------------------------+
  0     3     6                       30


And our waiting time calculation would be (0+3+6)/3 = 3ms, which is drastically
lower.  This is one of the main limitations of FCFS: the FIFO ordering is not
necessarily optimal.  The effect wherein a long process delays others is called
the **convoy effect**.

Note that FCFS is nonpreemptive.  There are no context switches.


SJF
...

With this in mind, a more suitable alternative seems to be **shortest-job first
(SJF)**.  Essentially, the processes are scheduled in order of increasing burst
time. Consider:


::

    Process            Burst Time (ms)
    -------            ---------------
      P1                    6
      P2                    8
      P3                    7
      P4                    3

Then the scheduling order would be P4, P1, P2, P3:

::

  +----+------+-------+--------+
  | P4 |  P1  |   P3  |   P2   |
  +----+------+-------+--------+
  0    3      9      16        24


Thus the waiting time  would be (0+3+9+16) = 7ms.  SJF is optimal in terms
of waiting time.  The problem is knowing the burst duration of the processes.

SJF is used in long-term shcedulers in batch systems.  (What is a potential
issue with this approach?) The user will supply an estimated duration when
submitting the job. 

With short-term scheduling there is no way to know the length of a burst, but
it can be estimated based on the length of previous bursts.  We can use an
equation for calculating the exponential average of previous bursts to get an
estimate of the current burst time.  For some value of a, 0 <= a <= 1:

::

  T_{n+1} = a*t_n + (1-a)*T_n


That is to say, we add a proportion of the previous burst time and our previous
estimate.  Expanding this formula gives

::

  T_{n+1} = a*t_n + (1-a)*t_{n-1}  + ... + (1-a)^j*a*t_{n-j} + ... + (1-a)^{n+1}*t_0.


Which indicates that older history has less weight than more recent history. Suppose
a=1/2. Then subsequently less weight is given to prior burst times.  Example with
a=1/2:

::

  burst       6   4   6   4  ...
  guess  10   8   6   6   5  ...


Note that SJF can be preemptive or nonpreemptive.  Preemptive SJF will preempt
the currently running processes and is sometimes called
**shortest-remaining-time-first** scheduling.

Priority
--------

SJF is a special case of **priority scheduling**, in which each process is
assigned a priority and scheduled on the basis of that.  In SJF, processes
could be assigned a priority which is the inverse of its estimated burst time.
For that matter, FCFS may be considered a special case of priority scheduling
in which all priorities are equal, and the processes are scheduled in the order
in which they arrive in the ready queue.

Integers are used to assign priority, although there is no agreement about
which direction (1 could be low or high).  We will proceed on the agreement
that lower numbers are higher priority.  Priorities can be assigned internally
(as the result of some OS calculation) or externally (user-specified, or based
on cost).

::

  Process     Burst Time      Priority
  -------     ----------      --------

    P1            10             3
    P2             1             1
    P3             2             4
    P4             1             5
    P5             5             2


The Gantt chart looks like the following:

::

  +----+-----+----------+-----+-----+
  | P2 | P5  |   P1     | P3  | P4  |
  +----+-----+----------+-----+-----+
  0    1     6         16    18    19


Priority scheduling can be preemptive or nonpreemptive.  A preemptive priority
scheduling algorithm will schedule new processes of higher priority before
older processes of lower priority.  In this case, low-priority processes can be
starved.  One solution to this is **aging**; as time passes, processes which
have been waiting in the ready queue gain priority gradually until they
eventually become high-priority enough to be selected for dispatch. 

Round-Robin
-----------

Designed specifically for time-sharing systems, **round-robin** is a scheduling
algorithm in which each process is given an equal share of time in rounds. The
share of time is called a **time quantum**.  The ready queue is used as a FIFO
queue. Newly-added processes are put on the tail of the queue. 

If the process completes before the time quantum, RR moves to the next process,
otherwise a timer will go off and cause an interrupt which will trigger a
context switch to the next process.

Example:

::

  Process    Burst Time
  -------    ----------

    P1            9
    P2            3
    P3            6


With a time quantum of 3ms, the Gantt chart would look like this:

::

  +----+----+----+----+----+----+
  | P1 | P2 | P3 | P1 | P3 | P1 |
  +----+----+----+----+----+----+
  0    3    6    9   12   15   18


The waiting time when using RR is often quite long due to its time-sharing
nature.  When calculating waiting time, it must be calculated per-process.
P1 waits for 9ms, P2 waits for 3ms, and P3 waits for 9ms.  Thus the total
waiting time is (9+3+9)/3 = 7ms.

It is important to select a time quantum which is much larger than the dispatch
latency.  This is so that the relative overhead can be minimized.  Setting the
time quantum too high can reduce responsiveness.  The relationship between
turnaround time and the time quantum is complex.  If the time quantum is too
large, RR reduces to FCFS.  

Multilevel Queues
-----------------

In a multilevel queue design, there may be multiple queues on a system.  A
process is permanently assigned to a queue based on its properties.  Higher
levels have higher priorities. Each queue may have a different scheduling
algorithm.  A common setup is to have foreground and background processes in
different queues.  In such a case, foreground may have RR (for responsiveness)
and background may have FCFS.

It is possible to have a design in which higher-priority queues must be
completely empty before jobs in lower-priority queues may be scheduled.  This
idea is similar to priority scheduling for individual processes, but it applies
to groups.


Multilevel Feedback Queues
--------------------------

In this design, processes can move between queues. Processes are separated
based on their CPU bursts.  I/O-bound and interactive processes go in
higher-priority queues.  Processes in lower queues age to prevent starvation,
then after some time, advance to a higher level.

Multilevel queues in general are defined by these parameters:

 * number of queues
 * scheduling algorithm for each queue
 * method for mapping process to queue
 * method used to determine upgrades
 * method used to determine downgrades

Thread Scheduling
================

First it is important to introduce the notion of a lightweight process (LWP).
This is a process which is mapped to a single kernel thread and shares the same
address space and system resources as the process to which it belongs.

In many-to-one and many-to-many models, the thread library schedules user-level
threads to run on an available LWP.  This is called **process-contention scope
(PCS)**, since the threads within a process compete for the CPU.  Typically PCS
is done according to thread priority.  The processes are said to compete because,
typically in the case of many-to-many, the number of kernel threads is less than
the number of user space threads.

To decide which kernel-level thread to schedule onto a CPU, the kernel uses
**system-contention scope (SCS)**.  Systems which use one-to-one models only
schedule threads with SCS; thus competition for CPU with SCS indirectly takes
place among all threads in the system.  


Multiprocessor Scheduling
=========================

If multiple CPUs become available, the useful feature of **load sharing**
becomes available, along with the potential responsibility of **load
balancing**.

It can be handled with **asymmetric processing**, wherein a single processor
handles scheduling, I/O processing, and other system activities. An alternative
is **symmetric processing**, which each processor is self-scheduling.  All
processors may have a common ready queue (shared memory), or each may have
its own private queue. 

Load balancing is typically required on SMP architectures because jobs in
their private queues may not be evenly distributed.  There are two approaches
to load balancing.  In **push migration**, a process will periodically check
load on each processor and if it finds an imbalance, it will move processes
from one queue to another.  In **pull migration**, an idle processor will
pull processes from another queue.

Suppose a process P1 runs on C1.  It had loaded some data tables into the
caches of C1.  Then C1 context-switches to P2, which then runs.  Meanwhile P1
is scheduled to run on C2.  In this case, P1 has lost access to the cached
information, and must now load from memory.  Beyond the dispatch latency
due to memory retrieval has been introduced.

To remedy this, processes can be assigned a **processor affinity**, which is a
"preference" for a processor which it had been running on prior to a context
switch.  When the scheduler schedules P1 again, it may wait for P2 to complete
before re-assigning it to C1. There are two variations on affinity; **soft
affinity** does not guarantee that the process will be re-scheduled on the same
processor, whereas **hard affinity** limits a process to a subset of
processors.

Processor affinity and load balancing can come into conflict if, for example, a
process P1 with affinity for a processor C1 is waiting for P2 to complete, but
it snatched by the idle C2 in a pull migration.  In this case the advantages
to processor affinity are lost. 

Multicore Scheduling
====================

When a process waits for data from memory to become available, it spends a
significant amount of time waiting.  These are called **memory stalls**, and
occur on cache misses.  In such situations, multiple threads can be scheduled
to run on a core so that the CPU is always being utilized during memory stalls.

::

  C M C M C M   
                  ...
    C M C M C M 

In this way, memory retrievals and CPU usage are staggered.  Multithreading can
be **coarse-grained**, as illustrated in the above diagram.  Context switching
only occurs on memory stalls.  However, context switching incurs overhead
because the instruction pipeline must be flushed.  **Fine-grained**
multithreading allows context switching at the boundary of an instruction cycle
but requires an architectural design for context switching.

Multicore systems require two levels of scheduling. First is software->hardware
thread mapping; second is how each core decides which hardware thread to run.

Real-Time CPU Scheduling
========================

**Soft real-time systems** provide no guarantee when a critical real-time
process will be scheduled, only that they will be given preference. 
**Hard real-time systems** do; a task must be serviced by a deadline.

**Event latency** is the amount of time between an event and when it is
serviced (press joystick, character jumps). On real-time systems, two types
of latencies might affect performance: **interrupt latency**, which is the
time of the arrival of an interrupt at the CPU to the start of the routine
that services the interrupt; and the dispatch latency. 

For soft real-time systems, latency must be minimized; for hard real-time
systems, it must be bounded in order to meet the deadline.  

Dispatch latency may have a **conflict phase** in which other processes
in the kernel need to be preempted, and in which lower-priority processes
release resources required by the now higher-priority processes.

::

  
  | (event) -------------------------------------------->  (response) |
  |                                                                   |
  | (interrupt)  |                                     | (execution)  |
  |              |         (dispatch latency)          |              |
  |              |                  |                  |              |
  |              |   (conflicts)    |    (dispatch)    |              |


As a result, a scheduler for a real-time system must support a priority-based
algorithm with preemption.  Hard real-time systems require additional
scheduling features, which we discuss next, after some definitions of the
characteristics of processes handled by such systems.

**Periodic** process recur; they have a fixed processing time *t*, a deadline
*d*, and a period *p*, such that 0 <= t <= d <= p. The **rate** of the process
is 1/p.

::

 ----------------------p ---------------------- p
 -------------- d        -------------- d
 -------- t              -------- t                  ...
 ========                ========
 period 1                period 2

A process may need to announce its deadline to the scheduler. Then using
an **admission-control** algorithm, the scheduler either admits the process
and guarantees it will be completed by the deadline, or rejects the request
as impossible.

The **rate-monotonic** algorithm schedules periodic tasks using a priority
policy with preemption.  Tasks are assigned priorities proportional to their
rate (if it requires the CPU more often, give it).  It is assumed that the
processing time of a periodic process is the same for each CPU burst (t is
uniform). 

Consider processes P1 and P2, where p1=50, p2=100, t1=20 and t2=35.  Also the
deadlines are equal to the periods.  Is it possible to schedule these?  To
answer this, we can look at the CPU utilization for each.  t1/p1=.4 and
t2/p2=.35, and the sum of these is .75.  Therefore the CPU is 75% utilized, so
it seems we can schedule the processes.  We would then schedule P1 prior to
P2 since its rate is higher. 

Rate-monotonic is optimal given its assumptions, but it has a
limitation. CPU utilization is bounded; it is not always possible to 
maximally utilize it.  The worst-case CPU utilization for scheduling N
processes is ``N (2^(1/N) - 1)``.  This implies that with one process,
CPU utilization is 100%.  With two, it falls to about 82%.

**Earliest-deadline-first (EDF)** is the same as rate-monotonic in all respects
except it assigns priorities according to deadline. 

Suppose P1 and P2 have p1=50, t1=25, p2=80, and t2=35. Then according to EDF,
P1 would first run because its deadline is earlier. It runs for 25 units; then
the next deadline for P1 is 75 units away, whereas for P2 it is 55 units away,
thus P2 gains priority and is scheduled. It runs for 35 units, then priority is
switched to P1, whose new deadline is 40 units away.  Priorities switch in
this fashion repeatedly.

**Proportional share** schedulers assign *T* shares among applications; each
application receives some *N* number of shares, ensuring it has N/T proportion
of total shares.  This type of scheduler works in conjunction with an
admission-control policy to guarantee that an application receives its fair
share of time. 
