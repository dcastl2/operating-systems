======================================
Chapter 2: Operating System Structures
======================================


What OS Structures is About
---------------------------

 * *Operating system structures* refers to the anatomy of an operating system.
 What are the core parts and components that make everything work together?


Operating System Services
-------------------------

 * Operating systems are understood in terms of their functional components.

 * In order to understand how everything fits together, we look at the services
 provided by an operating system.


Helpful functions
-----------------

 * **user interface**
 * **program execution**
 * **I/O operations**
 * **filesystem manipulation**
 * **communications**
 * **error detection**


Efficiency functions
--------------------

 * **resource allocation**
 * **accounting**
 * **protection and security**


-----------------------------------
User and Operating-System Interface
-----------------------------------


Interfaces
..........

 * In order to be at all useful, an operating system needs to have an
 interface.

 * Some servers do not have hardware interfaces, however they still
 support software interfaces in the event that interfaces are required.


--------------------
Command Interpreters
--------------------


Shells
......

 * Command interpreters are what we have been looking at.  The user types in a
 command, which points to an executable somewhere on the system, and that
 command is executed (via program execution service).

 * Windows has MS-DOS and PowerShell, and MacOS has terminal.

 * Linux has several **shells**; the most popular being *BaSH* or ``bash``, the
 Bourne-again SHell. There is also ``csh``, ``zsh``, and others.


Graphical User Interfaces
.........................


 * Xerox Alto was the first (1973).

 * The Macintosh desktop had the first multi-panel windowing interface (1984).

 * *Windows* gets its name from the window-managing GUI for MS-DOS; it was
 first developed in 1985.

 * The *X* windowing system was developed for Unix in the mid-80s at MIT.

 * Now phones have their own GUIs (2009).

 * In Linux terminology, there is a distinction between a *window manager*,
 such as fluxbox, openbox, etc. which does nothing but manage windows; a
 *desktop environment*, which is a full graphical environment with its own
 program suite; and a *window system*, like X.

 * Recently, a window system called *Wayland* was released as an alternative to
 X (2014).


Choice of Interface
...................

 * People who choose CLI may be system administrators, system programmers,
 computational scientists, or power users. Reasons to choose CLI:

   + more control
   + scriptable
   + faster once learned
 
 * People who choose GUI tend to be casual users. Reasons to choose GUI:

   + more user-friendly
   + lower learning curve


System Calls
------------


What are System Calls?
......................

 * System calls provide an interface to services made available by the
 operating system.

 * An example is ``read()``, which reads input from a file or device; or
 ``fork()``, which creates a new process.

 * System calls are accessed via an API such as ``libc``, the standard
 C programming library. 

 * Low-level functions in C often have a one-to-one correspondence with system
 calls.

 * Section 2 of the Linux manual pages contains detailed information about
 system calls (my OS has about 500 system call manual pages).


Types of System Calls
.....................

  * process control
  * file management
  * device management
  * information management
  * communication
  * protection


Process Control
...............

  * These are responsible for creating, deleting, loading, and executing
  processes; or getting or setting process information; or waiting, allocating
  or deallocating memory (since memory use is linked to processes).

  * ``fork()`` is an example of a ``libc`` function that creates a new process.
  
  * ``exit()`` triggers process exit, memory deallocation, etc.

  * ``wait()`` causes a process (e.g. child process) to finish executing

  * You may be familiar with ``malloc()`` for memory location; but in spite of
  being low-level, it is *not* a system call. The call for increasing heap size
  is ``sbrk()``.


File Management
...............

  * These are responsible for creating, deleting, reading from, or writing to
  files/directories; or getting or setting file/directory information.

  * ``open()`` creates a **file descriptor** for a particular file; which is
  a handler associated with file information in kernel space. ``close()``
  closes the file.

  * ``read()`` reads bytes from a file descriptor, ``write()`` writes bytes to
  a file descriptor.

  * ``mkdir()`` is a system call. Did you know that?


Device Management
.................

  * These are responsible for creating, deleting, reading from, or writing to
  devices; or getting or setting device information.

  * ``ioctl()`` is used for making requests of file descriptors.  ``ioctl(fd,
  CDROMEJECT, 0);`` can, for example, request eject of a CD-ROM.

  * In a Linux system, devices are treated like files. That gives them the
  advantage of interfacing with the same system calls as files. Take ``read()``
  for example, which can read from ``stdin`` as well as a file.

  * Devices are even objects of the filesystem. Examine ``/dev`` for a look
  at device files.



Information Maintenance
.......................

  * Get/set information.  Anything having to do with timers.  ``time()``, for
  example; also ``alarm()`` and ``sleep()``. 

    + Interesting fact: ``proc/timer_list`` has list of all timers on the system.

  * Others intersect with other services. ``stat()`` gets file status,
  ``getpid()`` gets a process ID.


Communication
.............

  * ``pipe()`` creates a pipe, a means of interprocess communication.

  * ``socket()`` used for client/server model communication.

  * ``shm_open()`` opens shared memory.

  * ``mmap()`` maps files/devices onto memory.


Protection
..........

  * ``chmod()`` changes file permissions, ``chown()`` file ownership.

  * ``umask()`` sets file mode creation mask; basically causes any files
  created by the process to assume certain permissions.


System Programs
...............

  * System programs are implemented to handle the most important and frequent
  system calls, or to perform simple operations that require a few system
  calls.

  * You may have seen some system programs you recognize in the form of
  system calls.

  * For some system programs, there is a one-to-one correspondence with
  system calls, like in the case of ``mkdir()``, or ``sleep()``.

  * System programs are detailed in Section 1 of the Linux manual pages.


OS Designs and Implementation
-----------------------------


Design Goals
............

  * Relates back to perspectives on operating system: user and system.

  * The user goals are concerned with user-end desires; speed, ease-of-use,
  safety.

  * The system goals are concerned with the people who write operating
  systems. It should be easy to maintain, efficient, etc.


Mechanisms and Policies
-----------------------

  * **policy**: what to do

  * **mechanism**: how to do it

  * *If the temperature rises above threshold, moderate the temperature* is a
  policy; but *slow the clock speed to minimum* and *shut down the machine* are
  mechanisms separate from the policy. 

  * We desire separation of policy and mechanism for flexibility in the
  operations of the system as standards evolve and hardware changes.


Implementation
--------------

  * Early operating systems were written in assembly.

  * Now written in higher-level languages such as C or C++. 

  * All kernels of major operating systems (Windows, Linux, Mach in MacOS) are
  written in C.

  * Operating systems courses are normally taught in C for that reason.


OS System Structure
-------------------


Structures
..........

 * monolithic
 * layered
 * microkernel


Monolithic
..........

 * In a monolithic kernel, all functionality is built into a single entity.

 * MS-DOS and early UNIX were monolithic because of limited hardware.

 * Monolithic kernels are difficult to maintain; they are inflexible because
 changes in hardware require changes in kernel code.


Layered Approach
................

 * In a layered approach, the functionality is built upon layers. The higher
 layers call lower layers, and so forth.

 * Layered approach can be hard to develop; requires strategy.

 * Example: swap vs. CPU scheduling. Which one should go first?


Microkernels
............

 * A microkernel supports mainly IPC, and minimal memory and process
 management. All extensions are developed in user space.

 * Advantages include a smaller, more portable, and more secure kernel,
 since it is small. 

 * The message-passing IPC framework can introduce unwanted overhead.
 Windows NT had a microkernel that suffered performance-wise due to
 system-function overhead.


Modules
.......

 * Some kernels are modular. Linux, for example. Modules can be listed with
 ``lsmod``, inserted and removed with ``modprobe``. These modules are primarily
 for device drivers and filesystems.

 * Modular designs are a fusion of layered/microkernel approaches.


Hybrid Systems
..............

  * Mac OS X is a layered system with Aqua GUI, Cocoa for Objective-C, and has
  a Mach microkernel and BSD (Berkeley Software Distribution) Unix kernel.

  * iOS uses a similar structure, but has media services built on top of its
  core services.

  * Android rests on a Linux kernel. Uses an Android runtime environment with
  core libraries and Dalvik VM; also SQLite, openGL, libc etc. libraries. 


OS Debugging
------------

  * Kernel supports printing of various messages; in Linux these are accessed
  via the ``dmesg`` command. 

  * Kernels also dump information on catastrophic failure (crash).


OS Generation
-------------

  * Refers to generation of an operating system at a particular hardware site.
  OS generation is part of the installation process.

  * An experienced user can modify the kernel sources for an operating system
  (using ``makeconfig``), then compile a kernel for that particular hardware.

  * An automated program can detect devices and select appropriate drivers for
  the system, however such programs tend to err on the side of caution and may
  end up producing an operating system which is too general for the hardware.

  * Or, all the code may be loaded all the time, and tables may be constructed
  to describe the system.


OS Boot
-------

  * Power button triggers execution of the bootstrap program in firmware (which
  is some form of ROM, and may be EPROM or EEPROM). Note that the bootstrap
  program actually executes in firmware, which in general tends to be slower
  than RAM. 

  * The bootstrap program looks in secondary storage ROM for a bootloader,
  which is a program to select and load the operating system. The bootloader
  is typically stored in the MBR (master boot record); or else on the first
  partition of the storage device.

  * The bootloader may untar/unzip the kernel if compressed and copy it into
  memory. Once copied, the instruction pointer (IP) is set to the first
  instruction (which is the ``init`` process).  Once this process starts, the
  system is *running*.


Questions
---------

  * What is a system call? What is the purpose of a system call?  Give a couple
  of examples of ``libc`` system call.  Finally, give an example of a ``libc``
  library function which is itself not a system call, but invokes a system
  call.

  * Why are memory management system calls considered to be part of process
  control? What is the relationship between memory management and process
  control?

  * Why, in some operating system architectures, are devices considered to be
  files? What is the advantage of treating a device as a file?

  * What are the three basic structures of an operating system? How do they
  differ? What type of operating system does your cell phone have?

  * Give an example of two policies and two mechanisms which may be linked
  any given way. 

  * What is the difference between a bootstrap program and a bootloader?
  Where do each reside? Why would a machine boot slowly even if it runs
  quickly?

  * Explain how a modular kernel design facilitates operating system
  generation.
