Definition of Operating System
==============================

  * An **operating system** the part of a computer system which is responsible for
    managing hardware and interfacing between hardware and application programs on
    the system. Alternatively stated, it is *the software which coordinates
    hardware with the rest of the software on the system*.  The precise definition
    is a subject of contention.

  * Operating systems (OSs) can be approached from a *user viewpoint* and a *system
    viewpoint*.  They are developed so as to strike a balancing point between *ease
    of use* and *resource utilization*, depending on the user needs and the
    hardware.  From the system view, OSs act as *resource allocators*, retrieving
    clock time, memory, and disk space for application programs. They also contain
    *control programs* for managing I/O devices and user programs.

  * The **kernel** is the core part of the OS; that is, the part of the OS which
    does not include system and application programs.  The kernel is responsible
    for hardware detection, process and memory management, filesystems and disk
    utilization, etc.


Computer System Organization
============================


Bootstrapping
-------------

  * A simple program called a **bootstrap program** is stored in **EEPROM**
    (electrically-eraseable programmable read-only memory), more generally known
    as **firmware**. The bootstrap program finds the OS kernel and loads it into
    memory, along with code for other system processes and **daemons**.


Interrupts
----------

 * An event such as a keyboard press signals an **interrupt** which travels via
   the system bus. Software may also trigger interrupts via system calls.  Most
   computer designs handle interrupts by assigning the pointers to interrupt
   service routines in low-memory; similar to a jump table, it is called an
   **interrupt vector**.

  * The interrupt causes the CPU to transfer control to a memory location in the
    interrupt vector, which runs a service routine.  To recover from the interrupt,
    the system stores the current address where it was interrupted (the instruction
    pointer), then restores it once the service routine is finished.


Storage
-------

  * There are four basic categories, in increasing order of capacity (and
    decreasing order of speed):

     + registers
     + caches
     + memory
     + disk

  * Registers, caches, and memory are **volatile**, which means they lose their
    contents when the device is powered off.

  * There are many sub-types of disk (solid-state, magnetic, optical, etc.).


Input/Output
------------

  * A **device** can contain its own registers and local buffer for storage.  A
    single-processor **device controller** is responsible for the transfer of
    data from the device hardware and its registers and buffer to the device
    driver.

  * The OS can make I/O requests to the device. A device driver accepts
    interrupts from device controllers and returns control to the OS.

  * Some devices completely bypass the CPU by transferring blocks of data
    to/from memory directly. These are **direct access memory** or DMA devices.


Computer Systems Architecture
=============================


Single-processor
----------------

  * Uniprocessor systems may have some form of **time-sharing** enabled which
    allows for multiple processes to appear to be executed simultaneously
    by switching between them.

  * Some devices have their own processors, which allow them to work
    synchronously. For example, a hard disk may have its own scheduling
    algorithms which can work in tandem with the CPU.


Multi-processor
---------------

  * Multi-processor systems may share a bus, clock, memory.

  * A few advantages:

    + Increased throughput. More processes running synchronously, or increased
      parallelization of a single process.

    + Economy of scale. More processors in a single chassis is less expensive
      than multiple uniprocessor systems (see clustering below).

    + Increased reliability.  More graceful degradation and fault tolerance
      than in uniprocessor systems. 

  * Two kinds of processing:

    + Asynchronous. Boss/worker model; boss assigns tasks to workers.

    + Synchronous. Any processor can handle any task; memory is shared.

  * Multicore machines share L2/L3 caches but have their own L1 cache and
    registers. All multicore systems are multiprocessing systems, but not all
    multiprocessing systems are multicore.
    

Clusters
--------

  * Clusters are multiple systems connected via some means of data transfer 
    (usually Ethernet or fiberoptic).

  * Among the first clusters were Beowulf clusters, which were old 
    uniprocessor computers connected via Ethernet. 


Operating System Structures
===========================

  * Multiprogramming is programming for multiprocessor systems. The degree of
    multiprogramming is the extent to which multiple processes are being 
    supported on a system.

  * Job scheduling, also known as long-term scheduling, is concerned with
    choosing processes to place in memory.

  * CPU scheduling, also known as long-term scheduling, is concerned with
    which process to schedule next.

  * Virtual memory is "physical memory plus disk", or physical secondary
    storage.  An operating system can appear to have more memory than it
    actually does.
    
    * The operating system uses page swap operations to place unused pages from
      memory into the disk so pages are freed from RAM.


Operating System Operations
===========================

  * Operating systems act as resource allocators, and are also responsible
    for program control.

  * Operating systems are interrupt-driven. The system will normally wait 
    idly until a user interrupts, then go about some service routine.
    Interrupts can come from software.

    * A **trap** is a software interrupt, also called fault or exception.
      
    * Interestingly the name "segmentation fault" comes from the fact that
      when data is accessed outside segments which were allocated for or
      which the program does not have permission to read, it triggers a
      software interrupt which stops execution of the program.

  * The operating system is responsible for ensuring that processes and
    users are unable to interfere with each other.


Dual/Multi-Mode Operation
-------------------------

  * Most operating system designs have a dual-mode; one for the user, which is
    restricted from interfacing directly with the hardware, and another for the
    system, which is not. Others have multi-mode which includes permissions which
    fall in the middle.

  * For a process executing a system call, the process may switch modes during
    the system call. A mode bit is set which allows the process to change modes
    temporarily to execute the system call code.


Timers
------

  * A timer is used for dealing with infinite loops and preventing failed system
    calls. A fixed timer sends an interrupt after a fixed amount of time, and if
    a process does not respond, the process can be terminated.

  * A variable timer can use a variable duration combined with a counter that
    checks the process state. 


Process Management
==================

  * A process is a program running in memory.  Processes are active, whereas
    programs are passive.  Processes may require:
  
    + Time
    + Memory
    + I/O
    + Files

  * Operating systems are responsible for scheduling processes,
    creating/deleting them, suspending/resuming, as well as process
    synchronization and interprocess communication.


Memory Management
=================

  * Processes require an address in memory in order to be executed.  They thus
    require memory allocation. When finished, they must be deallocated.

  * Also, on a multiprogrammed system, many processes must be kept in memory
    at once to run at the same time. That requires memory management.

  * Operating systems are responsible for keeping track of which parts of memory
    are in use and which processes to keep in memory and which to swap out.
  

Storage Management
==================

  * Mainly filesystem management.


Filesystem Management
---------------------

  * Reponsible for creating/deleting files/directories, manipulating
    files/directories, mapping files to secondary storage, and in some systems,
    backups.


Caching
-------

  * Cache is intermediary between registers and memory. When data and programs
    are loaded from memory, they are first loaded in blocks into a cache, which
    can then be quickly transferred to the registers. Caches are faster than 
    memory but also smaller.

  * Caches are between registers and memory in size:

    + Registers - bytes
    + L1 Caches - kilobytes
    + L2 Caches - megabytes
    + Memory    - gigabytes
    + Disk      - terabytes

  * Prevents latency from instruction fetches during program execution, which
    allows programs to run much faster.


I/O Subsystems
--------------

  * I/O devices require memory management. Devices might need buffers and
    caches managed.

  * Devices need drivers; the operating system is responsible for handling
    device interrupts.
  

Kernel Data Structures
======================

  * Kernels might use

    + Linked list
    + Stack
    + Queue
    + Tree
 
 * Also a bitmap may be used, for example, to indicate pages in memory which
   are in or out of use. A bitmap maps to some larger storage unit (e.g. a 4KB
   page) where each bit assumes one of two values indicating some boolean 
   attribute.

