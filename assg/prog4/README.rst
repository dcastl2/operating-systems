Homework 4
==========

Select up to 64 points worth of problems.  You may earn +N extra credit points
if you submit the assignment N<=8 days in advance of the due date (Sunday at
6:00:00 PM on 10/23/2016).


1. Create a Linux Live USB stick.
     [32] Obtain an ISO of either *Kali* or *Tails* and fashion a bootable USB
     stick from it.  To demonstrate it, you can (a) show it in-class, (b) in my
     office hours, or (c) take a video of it booting on a machine of your
     choice, making sure to prove it is *you* who is booting the USB stick, and
     submit a file called ``link.txt`` linking to the video (you can use
     whatever video sharing solution you like).  

     Only your p_copy timestamp will count for the purpose of determining extra
     credit due to initiative; this matters if you choose (c).  If you choose
     to demonstrate the USB stick via methods (a) or (b) you need only do so
     before the homework deadline.

     If you choose to create one, you should keep it with you.  For the asking,
     I will show you how to use the ``mount`` command to bypass user
     authentication on a typical machine, among other things.


2. Brute-force password decryption using multi-threading.
     [32] Encryption algorithms work by operating on a password to produce a
     hash.  Brute-force password cracking works by applying an encryption
     algorithm to a range of possible passwords, and checking if each of the
     resulting hashes turned up by the encryption algorithm is equal to an
     acquired hash. 

     Naturally, this takes a long time. Anything which is known about the
     password helps a brute-force attempt--such as knowing that the password
     has only lowercase characters, or that it is exactly eight characters in
     length, and so forth.

     A file called ``crack.c`` is provided which contains a serial decryption
     algorithm for use with Linux ``crypt(3)``, and a file called ``hash``
     which contains a password hash for the password ``abba``.  Run it and
     observe how it works.  It assumes the password is 4 lowercase characters
     and that the salt is also lowercase characters.  
     
     Write a multi-threaded version using pthread to run the serial algorithm
     on all possible four-character lowercase-letter passwords, and check to
     see if the hashes are equal.  If they are, output the password to stdout
     and terminate the program.  Use four threads.  Call it ``crack.c``, as the
     original is called.
     
     You will need to be careful with pointers; in particular, ``crypt`` uses
     only one pointer to reference its result, so you will need to avoid race
     conditions in the multi-threaded version.  Use a mutex lock during calls
     to ``crypt`` and data copies from the pointer returned by crypt.


3. A multi-threaded file server.
     [32] Typical web servers are file servers: they allow multiple users to
     download files from the server concurrently.  A multi-threaded file server
     does just that; it allows for multiple clients requesting different files
     instantaneously to download them concurrently.  Such servers typically
     have limits imposed on them to handle request-based DDoS attacks, such as
     only allowing *n*-number downloads at one time, or restricting bandwidth.
     
     Write a multi-threaded sockets-based client/server system ``server.c`` and
     ``client.c`` using the pthread library.  The client program should accept
     as command-line arguments an IP address and a path to a file.  The server
     should send the requested file back to the client, which should save it in
     the current directory by its basename.  
     
     For each client request, have the server create a new thread to handle it.
     You will need to use a counting semaphore to ensure that at most four
     threads are running at one time.  If the server is busy (with four threads
     running), it should honor the next client request as soon as it is able.


4. How system command options are enabled; how manual pages are written.
     [32] Command-line options can be accepted in a more fluid manner using the
     ``getopt`` library.  The ``getopt`` library allows for options to be given
     in any order, and in long or short form, using a simple minimum-length
     description in the code. See ``src/sum.c`` for an example.

     Also included is a manual page for the system command, which can be viewed
     with ``man -l sum.1`` (-l for local).  Study the syntax to get a feel for
     how a manual page is structured.  You can read more about how to properly
     create manual pages on-line.

     Write a program ``cab.c`` which copies a segment of bytes from one file
     into another. It should take the following options:

       * ``-i`` or ``--input`` followed by a filename to read from. 
         If not specified, it should read from stdin.

       * ``-o`` or ``--output`` followed by a filename to write to. 
         If not specified, it should write to stdout.

       * ``-s`` or ``--start`` followed by a number in hex to start at.
         If this is not specified, it should start from 0.

       * ``-e`` or ``--end`` followed by a number in hex to end at
         If this is not specified, it should end at the EOF of the input file.

       * ``-n`` or ``--num`` which is a number of bytes to copy.  This
         must not be used in conjunction with both of the above options.

       * ``-v`` or ``--version`` and a help message displaying a brief
         summary of the options.

     The start and end values are inclusive (those bytes are copied).  Also,
     write a manual page for this program, giving its description, synopsis,
     option list, author information, and so forth. Call this ``cab.1``. 

