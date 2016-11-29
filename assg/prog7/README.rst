Homework 7
==========

You may earn +N extra credit points if you submit the assignment N<=8 days in
advance of the due date (Sunday at 6:00:00 PM on 12/09/2016).

Note that this assignment is optional.  If you opt to do it, your lowest
homework grade will be dropped.


1. Implementing your own filesystem.
     [64] Write a program which implements a filesystem called ``txtfs``. Your
     txtfs will be used to store text files.  The filesystem itself shall be
     stored *as a file* (call it ``filesys``).  The program should be started
     with the filesystem as an argument: ``txtfs filesys``, for example.  From
     there, the program should place you in the root of your filesystem, and
     support six commands:

       + ``mkdir``, which should support the creation of new directories;

       + ``create``, which should accept a filename as an argument and allow
         the creation of a new text file--it should accept text input until
         the user enters EOF on a single line;

       + ``cd``, which should change into directories in your filesystem; it
         should support changing to the parent directory as well

       + ``ls``, which should list the contents of the current directory; 

       + ``cat``, which should print a text file to stdout if the target is
         in fact a text file; and finally

       + ``quit``, which should quit the program and save the results back
         to file. 
         
         
    Note that this means you will have to load the results into memory before
    you make changes to the filesystem with your commands, because your
    filesystem objects must be allowed to grow.  You don't have to support
    shrinkage (e.g. via deletion).

    For your filesystem inodes, use a data structure such as the following:

      .. code:: cpp

         struct inode {
           int object_type;           // is it a file or directory
           int num_inodes;            // if dir, # of inodes inside
           struct inode **inodes;     // pointers to those inodes
           int size_data;             // if file, size of data stored
           void *data;                // pointer to the data
         };

    This is a suggestion. You are free to modify the data structure in any way
    which makes it easier for you, as long as your inodes do not use an undue
    amount of space. At the very least, you will need a recursive struct so
    that your filesystem will be a tree.

    Your filesystem object must be stored as efficiently as possible without
    compression, which means you will need to store it as a binary object.  One
    of your greatest challenges will be saving and loading the data. You will
    need to serialize the filesystem data when you save it so that it can be
    read each time you load it.

    Name this ``txtfs.c`` if you write a monolithic code.  You are free to
    write a multi-source program (create a library of functions, for example),
    in which case you can name your sources whatever you like--but if you do
    so, you must supply a Makefile.
