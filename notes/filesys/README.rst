Filesystems
===========

File basics
-----------

A **file** is a logical storage unit. Several types:

  * Plain-text file
    + Source file
    + Notes
  * Binary files
    + Executables
    + Objects

File attributes
---------------

Files have attributes:

 + **Name**, so that a file may be referenced in a human-readable
   format

 + **Identifier**, so that a files can be efficiently referred to
   by the operating system

 + **Type**, to distinguish between types of filesystem objects,
   such as files and directories

 + **Location**, or where it is within the filesystem tree

 + **Size**, so that only the required data may be loaded

 + **Protection**, so that only authorized users are able to
   access it

 + **Time**, including access and modification times

 + **User**, that is what user or group owns the file

In Linux systems, these attributes can be listed with ``ls``.  ``chmod`` can
change permissions, ``chown`` can change ownerships, and ``touch`` can
manipulate timestamps.

File operations
---------------

Operations on files include:

  + **Creation**: the space must first be allocated, then the entry in
    the filesystem must be made

  + **Writing**: like creation, space must be re-allocated; also the
    system must keep a *write pointer* to the location where the next
    write is to take place

  + **Reading**: the system must keep a *read pointer* to the location where
    the next read is to take place; both read and write operations use a
    *current-file-position pointer*

  + **Repositioning**: the above-mentioned pointer is repositioned to
    give a different value, also known as a *seek*

  + **Deletion**: must search the directory for the file, de-allocate
    the space, and erase the directory entry

  + **Truncation**: erasing a file but keeping its attributes, setting
    the file length to zero and releasing the file space

Other operations include appending, renaming, etc.; many file operations can be
understood in terms of changes to file attributes or the file data and its size
attribute.

The open-file table
-------------------

The OS keeps an **open-file table** so that, when a program requests a file
operation, its index in the table may be used (instead of searching the
directory tree for the file once again).  This is the purpose of the
``open(2)`` system call; ``open(2)`` searches for the file once, then
binds an index (the file descriptor) to the file location. 

``open(2)`` can also take permissions requested by the process, which are
checked against the permissions assigned to the file.  If they match, the
permissions are granted; otherwise an error is generated. 

``open(2)`` can be more complicated when multiple processes are allowed to read
from or write to files at the same time.  In this case, a system-wide table may
be kept; whenever a process opens a file, its entry is added to the system-wide
table.  If another process attempts to open it, it checks the system-wide table
for the entry, and simply makes a pointer to it.  The system-wide table may
have an *open count* to tell how many processes have opened the file. 

In summary, several pieces of information are associated with an open file:

 + **File pointer** to the last read/write location, which is kept in the
 process-wide table since processes may be reading from different locations

 + **File-open count**, which is in the system-wide table

 + **Disk location**, which may be kept in the system-wide table, and is
   used primarily so that the OS does not have to find the file in the
   directory hierarchy for each file operation

 + **Access rights**, which are kept in the per-process table, since each
   process may request different rights to the file


Locking
-------

A system-wide table may support locks and lock operations to prevent hazards on
files. These include **shared locks** in which several processes can acquire
the lock concurrently, and **exclusive locks** which only one process at a time
can acquire. These may be **mandatory** or **advisory**. In the former case, no
other process which requsts an exclusively-locked file may access it.  In the
latter case other processes are not prevented; it is up to the programmer to
manually lock the file.

Types
-----

For managing file types, a common scheme is to make the file type a part of the
name of the file (an extension). In some operating systems, there is a creater
attribute giving the name of the program which created it.  This allows for the
OS to provide default behavior for opening the file (e.g. a word processor
opening a file that was originally created by it).  

In UNIX systems, there is a crude **magic number** system which roughly
indicates the type of the file, but not all files have magic numbers, and magic
numbers are not always specific.  For some files, the type can be guessed based
on an examination of a combination of file attributes, magic number, and data.
The utility ``file`` can do this. 

File types give an indication to the program of the required structure of the
file.  Some object data, for example, may be stored in a binary format which
depends on a pre-established protocol to read it correctly. 

Internal structure
------------------

Disk systems normally represent file locations in terms of **blocks** (or
physical records) and their offsets.  There are normally predetermined block
sizes and offsets.  A common block size is 512 bytes; this way a location can
be obtained with a 2-tuple (e.g. <2, 64> refers to byte 1024+64=1088). 

There are also **logical records**, which are like blocks but which reside
in memory. If a logical record size is 1 byte, then the file is treated as
a stream of bytes, as in the case of the UNIX operating system. All physical
operations are done in terms of blocks; conversion to logical records to
physical blocks is a problem we have seen in paging.

The logical record size, physical block size, and **packing technique**
determine how many logical records are in a physical block. Packing can be done
by either an application program or the OS.  Since disk space is always
allocated in blocks, some part of the last block of any file will be wasted, up
to 511 bytes in the case of a 512-byte block. The worst-case scenario is to
have a disk populated with files requiring 513 bytes, which may waste a
significant portion of the disk space.  This is *internal fragmentation*.

Access methods
--------------

**Sequential access**.  The simplest access method is sequential access, in
which information in the file is accessed in order, one record after the other.
The file pointer can be reset to the beginning, and some OSs support seek
operations forward or backward by n bytes.  Operations include ``read_next()``
and ``write_next()``.

**Direct access**. Also called relative access; a file is made of fixed-length
logical records that allow programs to read and write records rapidly in no
particular order. The file is viewed as a numbered sequence of blocks or
records; thus we may read block 14, then 53, then 7.  Databases are often of
this type.  Operations include ``read(n)`` and ``write(n)``, where *n* is the
block number.  This is normally a **relative block number**, or block number
relative to the start of the file.

This method could be used to find data in a file quickly. We may have a hash
function for data used to determine the block that data is stored at; then when
we wish to read a value, we may use the hash function to find the block number.

How does a system satisfy a request for record N in a file? Assuming we have
logical record length L, the request for N is turned into an I/O request for L
bytes starting at byte location L*N within the file. 

**Indices**. Other access methods can be built on top of direct access. An
**index** may contain pointers to various blocks within a file.  Suppose a
retail-price file contains UPC codes with 10-bit product information and 6-bit
price information.  If a disk as 1024 bytes per block, we can store 64 records
per block since 16*64=1024.  A file of 256 records would occupy four blocks. If
we sort the file by UPC, we can define an index which has the first UPC in each
block.  Then we can use binary search on the index to find a target UPC.

With large files, the index may take up too much space in memory.  A solution
is to keep it on disk, then create a secondary index to reference the primary
index.  This is akin to multi-level paging schemes. 

Partitioning
------------

Disks can be broken into subdivisions or **partitions** to hold multiple
filesystems, though they need not hold anything (could be unformatted raw
space).  Any entity containing a filesystem is generally known as a **volume**.

Information about files in the system is also contained in a **device
directory** or **volume table of contents**; which we know simply as a
**directory**.

Filesystem types
----------------

There are many types of filesystems. Common ones include:

 + **ext**, general-purpose Unix/Linux filesystems 
 + **xfs** for large files
 * **reiserfs** for many small files
 * **ntfs** for Windows
 * **vfat** universally-readable old Windows fs type
 * **hfs** for Mac

Also, there are some special-purpose filesystems:

 + **tmpfs**, held in memory
 + **objfs** for kernel modules
 + **lofs** for loopback devices
 + **procfs** for holding processes


Directory overview
------------------

When considering directory structure, there are several operations
to keep in mind:

 + **Searching**
 + **Creation**
 + **Deletion**
 + **List**
 + **Rename**
 + **Traversal**

**Single-level directories**.  All files are kept in one directory.  The
problem is that this is difficult to search, name collisions may occur, and
security is undermined in a multi-user system.

**Two-level directories**. Each user has his own **user file directory** (UDF).
When a user refers to a particular file, only his own UDF is searched. Now,
name collisions are only internal to a user, and each user's data is easier to
secure.  However, the search time is still high, and users are isolated from
one another such that sharing data becomes impossible (unless we permit a user
to create files under another user's UDF and set permissions to them).

Another issue is system programs--where are these stored?  We could create a
UDF for the system, and supply a **search path** to it to give the location of
system utilities.  If a system utility is not found in the system UDF, it then
searches the user's UDF.  In Linux, this is the defined by the ``PATH``
environment variable.

**Tree-structured directories**.  In this scheme, directories form a tree,
and we maintain the present-working directory (``PWD``) for applications
that interface to the directory tree.  Path names can be of two types:
**absolute** and **relative**. 

An important policy decision is how to handle directory removal. Some OSs
will not permit the deletion of a directory unless it is empty (such as with
the ``rm`` command), but may provide a flag to indicate specifically that all
directory contents are to be deleted.  Deletion may be handled by a pre-order
traversal on the directory; a filesystem object is deleted after a the traversal.

Acyclic-graph directories
-------------------------

Consider two programmers who want to share the same directory from within their
home directory.  An **acyclic graph** allows sharing.  In this setup, a shared
folder is located somewhere outside of each user's home directory.  

In the most common solution, a **link** to that shared directory is made from
within each users's home directory.  The link is an indirect pointer to the
shared directory.  (Another solution is to keep duplicates of the data, but
this is space-inefficient.) In Linux, links can be made with the ``ln``
command.

An issue arises in traversal.  We do not want to traverse the filesystem
more than once.  We must have methods in place to avoid cycling.

Another policy decision involves the deletion of data linked to.  When is
it acceptable to move a file or directory pointed to by a link?  What is to
be done with the link?  In Linux systems, the default behavior is for the
link to become defunct (there is no warning).  An alternative is to preserve
the file until all links are deleted, or allow an option such that when a
file is deleted, its links are as well.

General graph directory
-----------------------

This type of directory structure supports cycles.  Issues arise in traversal;
cycle detection algorithms are computationally expensive.  A cheap solution is
to limit the number of directories traversed through during a search.



