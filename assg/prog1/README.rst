Homework 1
==========

Select up to 64 points worth of problems.  You may earn +N extra credit points
if you submit the assignment N<=8 days in advance of the due date.

1. A script for reviewing notes and codes.
     [16] As the course unfolds, the ``README.rst`` in each directory in notes/
     will have an ordered list of files you should read (see the example in
     shell/). It would be useful to automate the process of reviewing them.
     
     Write a script which can, for all the codes mentioned in ``README.rst``
     (in the order they are mentioned) do the following: print the code
     syntax-highlighted to stdout (see the manual page for ``highlight``), [2]
     number-line [2] the code/note, wait for the user to hit Enter [2], then
     clear the screen [2].  The directory to use shall be taken in as a
     command-line argument (thus, the script should be runnable outside of the
     current directory) [2]; if no argument is given, it should act on the
     current directory if a README.rst exists in the current directory [2].
     Use the commands ``file``, ``highlight``, ``nl``, ``read``, and ``clear``.
     Document the script with comments [4].  Call this ``review.sh``.  As long
     as you meet the specifications, you are free to personalize your script
     however you like.

2. A script for compiling and running code.
     [16] Write a script utilizing the ``smartlog`` library which should accept
     the name of a source file (with a .c or a .java extension) [2], then do
     the following: print the code syntax-highlighted to stdout [2], compile
     the code [2], then on the condition the code compiled successfully, run it
     [2].  Assume the source is such that the compilation and running process
     is simple (e.g.  ``javac Hello.java; java Hello`` or ``gcc hello.c -o
     hello; ./hello``).  Document each step of the script with the ``smartlog``
     logging functions [4], and in particular print failure messages on
     file-not-found, compilation, and run errors, or if the extension does not
     match [4].  Call this ``examine.sh``.  As long as you meet the
     specifications, you are free to personalize your script.
     
     See ``src/`` for an example of a script that uses the ``smartlog``
     library.

3. A POSIX-compliant file copy.
     [16] Write a POSIX-compilant version of the ``cp`` command using C library
     function calls, as described in Sec 2.3 (System Calls) [4]. except mimic
     the behavior of ``cp`` (it should be non-interactive, accept command-line
     arguments; replace the destination file by default, etc.) [4]. In your
     version, include a progress bar which shows the file copy progress in-line
     (you will need to use a trick that involves printing a carriage return)
     [4].  Call this ``copy.c``.  Indicate in comments all of the system calls
     which are triggered by calls to ``libc`` functions [4].

4. Write a kernel module.
     [16] If you select this problem, you will need to demonstrate it prior
     to the assignment due date, though you may submit your code earlier for
     the purpose of determining extra credit. You must demonstrate to receive
     the credit, however.

     If you have your own Linux device (or a LiveCD/LiveDVD on your laptop),
     you may write a simple kernel module (per the Chapter 2 Programming
     Projects: Part I--Creating Kernel Modules), then demonstrate module
     insertion and removal, providing evidence via ``dmesg`` output.  Call the
     module ``simple.c``.  If you are able to write the kernel module from
     memory while I watch, and demonstrate its use, I will give you a fox
     sticker (+1).

5. A study guide.
     [16] For every section and subsection of Chapters 1, write detailed notes
     on the section, summarizing its key points.  Break down the subsections to
     key concepts (terms, facts, examples); be as concise, but comprehensive as
     possible [8].  Explain all of the diagrams; reference them by number [4].
     Use ReStructured Text to format the notes [4].  Call this
     ``ch1-notes.rst``.

     a. A comprehensive study guide.
          [16] For an additional 16 points, you may do the same for Chapter 2
          (Operating System Structures) according to the same specifications
          as the above problem; but only if you have done a study guide for
          Chapter 1.  Call this ``ch2-notes.rst``.


6. Overview questions.
     [16]  Answer **all** of the questions at the end of Chapter 1 (there are
     30 total) [15=30x1/2]. Use ReStructured Text to format your answers [1].
     Call this ``ch1-questions.rst``.

     a. Operating Systems Structures questions.
          [16]  For an additional 16 points, you may do the same for Chapter
          2; but only if you have answered the Chapter 1 questions.  Answer
          questions 2.1-2.24 [12=24x1/2]. In addition, answer 2.25; give a
          thorough discussion [3].  Use ReStructured Text to format your
          answers [1].  Call this ``ch2-questions.rst``.

7. **Bonus points**: do everything.
     [+8] If you do all of the above to 100% completion, then you will get a
     feeling for what it is like to be me. It may provide perspective for those
     of you who are considering a career in academia.

     If you choose to do so, then for your extraordinary discipline, I will
     award you +8 on top of the 64/64 cap, in addition to extra credit you
     earn for turning it in early; and finally, an owl sticker (+1).
