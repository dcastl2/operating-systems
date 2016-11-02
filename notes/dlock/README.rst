Deadlocks
=========

A **deadlock** is a situation in which processes are stalled because each is
waiting for the acquisition of a resource which other processes are holding.
An illustration comes from Kansas legislature in the early 20th century:

::

  When two trains approach each other at a crossing, both shall come to 
  a full stop and neither shall start up again until the other has gone.

A process may request, use, then release a resource.  May be system calls, as
in the case of files (``open()``, ``write()``, then ``close()``).  Suppose that
two processes P1 and P2 hold files F1 and F2.  Now P1 requests F2 while it
holds F1; and P2 requests F1 while it holds F2.  The processes are deadlocked.

Necessary conditions for deadlocks:

  + **Mutual exclusion**.  A resource must be in a nonshareable mode. Only
    one process at a time can use it.

  + **Hold and wait**. A process must be holding a resource and waiting for
    the acquisition of another resource which is being held by another
    process.

  + **No preemption**. Resources cannot be preempted. Can only be released
    by a process holding it.

  + **Circular wait**.  There must be a cycle in the resource requests.


Resource Allocation Graphs
==========================

We can model resource request and assignment using a **system
resource-allocation graph**.  This graph is defined by a set of vertices and a
set of edges.  Vertices can be processes (circles) and resources (squares).
Edges can be **request edges** which are P->R (process P requests resource R),
or **assignment edges** which are R->P (resource R is assigned to process P).
Also, resources can have multiple instances.  For example, a semaphore may
control a number of access of threads to a network device; or there may be a
limit on the number of threads which can read from a database.

Example:

  + P = { p1, p2, p3 }
  + R = { r1, r2, r3, r4 }
  + E = { p1->r1,  p2->r3,  r1->p2,  r2->p2, r2->p1,  r3->p3 }

Also, there are two instances of r2 and three instances of r4.

It can be shown that there is no deadlock in situation represented by this
graph because there are no cycles in the graph.  If we add an edge p3->r2,
there is then a deadlock. 

If resources have only one instance and there is a cycle, there is a deadlock.
If a resource has multiple instances and there is a cycle, there may not be a
deadlock (if it is possible for another process to release a resource requested
in the cycle).  


Deadlock Prevention
===================

We can deal with it in one of three ways:

 + Deadlock prevention or avoidance
 + Detection and recovery mechanisms
 + Ignoring the problem

**Deadlock prevention** usually involves having a protocol to prevent
deadlocks.  **Deadlock avoidance** requires that the OS be given additional
informaiton in advance about which resources will be requested during the
process lifetime.  Avoidance is softer than prevention in the sense that
without an intervening mechanism to stop it, a deadlock is possible.
Prevention is harder in that protocol prohibits deadlock.

Prevention works by removing the hold-and-wait, no-preemption, or circular wait
conditions.

**Hold and wait**.  (a) One possibility is to mandate that a process request
all resources it requires at the beginning of its execution.  This, however,
can starve other processes (and defeat the point of multi-threading).  (b) A
variant of this requires that when a process requests a resource, it release
any resources it is holding (e.g.  ``close()`` a file before requesting
another).  This ensures there is at most one edge tied to a process.

**No preemption**. Also, we could allow preemption.  (a) If a process p1 is
holding resource r1, requests a resource r2 that cannot be fulfilled
immediately, then r1 is preempted (released).  (b) Alternatively, if a process
requests a resource, we check if it is available. If so, assign it; else if it
is assigned to processes waiting for another resource, preempt it; else wait.

**Circular wait**. Create map F: R->N, where N is the set of natural numbers.
(a) Initially any process p can request any number of instances of any resource
ri.  Thereafter p can only request rj iff F(rj) > F(ri).  (b) Alternatively we
require that if p requests rj, it must release all resources ri s.t. F(ri) >=
F(rj).  

In such a situation, a circular wait cannot exist.  To prove this (by
contradiction), assume that one does.  Assume process pi in { p1, p2, ..., pn }
is waiting for resource ri, which is held by p_{i+1}, also pn is waiting for
p1.  Since p_{i+1} is holding ri for while requesting resource r_{i+1}, we must
have F(ri) < F(r_{i+1}) for all i.  But this means F(r0) < F(r1) < ... < F(rn)
< F(r0) and therefore F(r0) < F(r0), which is absurd; therefore there can
be no circular wait.


Deadlock Avoidance
==================

Simple model requres that each process declare maximum number of resources of
each type it needs.  Given this, it is possible to ensure that the system never
enters deadlock.

A state is **safe** if the system can allocate resources to each process in
some order and still avoid a deadlock.  Formally, it is safe iff there is a
**safe sequence**. A sequence of processes <p1, p2, ..., pn> is a safe sequence
if for each pi, the resource requests that pi can make can be satisfied by the
available resources plus the resources held by all pj, j<i.

Thus if the resources that pi needs are not immediately available, pi can wait
until all pj have finished.  When pj have finished, pi can obtain its
resources, complete its task, release its resources and terminate...  if no
such sequence exists, the system state is said to be **unsafe**.

Safe states are never deadlocked states; all deadlocked states are unsafe
states; but not all unsafe states are deadlocked states.  An unsafe state
may lead to a deadlock.  As long as a state is safe, the OS can avoid unsafe
states and thus deadlock.

Banker's Algorithm
==================

Banker's algorithm for judging system safety is for systems with multiple
resources of a type.  Essentially, the algorithm simulates resource
acquisition.  Suppose there are *m* types of resources and *n* processes.
Banker's algorithm requires these data structures:

  * *V* of size *m*, which indicates the number of available resources
    of each type.

  * *M*, a matrix of size *n x m*, which indicates the maximum demand
    for the ith process of the jth resource.

  * *A* of size *n x m*, which indicates the number of resources 
    of a type allocated to a process

  * *N* of size *n x m*, which indicates the need of a process for
    a resource.  N = M - A.

  * Define *W* of size *m*, which indicates the number currently available
    (working) resources.  

  * Also define *F*, a boolean vector of size *n* which indicates if
    a process is finished or not.

Also if X and Y are vectors, X <= Y iff for all i in [1, n], Xi <= Yi.
The safety algorithm is as follows:

  1. Set *W = A* and *F = 0*.

  2. Find index *i* s.t.:

     a. *Fi  = 0*.
     b. *Ni <= W*.

     If no such i exists, goto step (4).

  3. Set *W = W + Ai* and *Fi = 1*; then goto step (2).

  4. If *F = 1*, the system is safe; else unsafe.

Intuitively, the algorithm loops, finding the next process which is not
finished whose needs are less than what is available. If such a process exists,
add those resources allocated to it to the working available resources, flag
the process as finished, and repeat.  If no such process exists and if all
processes are finished, the system is safe; but if there is a process which is
not finished, the system is unsafe (because then there exists a process with
unmet needs).

The resource-request algorithm determines if requests can be safely granted.
For it we require *R*, an *n x m* matrix of requests.  We define the algorithm
for a process *Pi* as follows:

  1. If *Ri <= Ni*, goto step (2), else raise an error condition (it is
     requesting more than it needs).

  2. If *Ri <= Ai*, goto step (3). Otherwise *Pi* must wait since the
     resources are not available.

  3. Modify the state as follows:

  .. math::

      V  = V  - Ri
      Ai = Ai + Ri
      Ni = Ni - Ri

  4. Finally, test safety of this new state with the safety algorithm.

