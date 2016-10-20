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
  | P4 |  P1  |   P2  |   P3   |
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


