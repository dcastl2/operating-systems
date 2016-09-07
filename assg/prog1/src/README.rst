The SmartLog Library
====================

I wrote a library for better logging functionality in BaSH scripts. It allows
the user to output log messages similar to kernel output messages, complete
with color-coding and tags indicating the type of message.

Its intended use was to document scripts both internally and during run-time,
so that a user would know exactly where the script failed.  Its core functions:


Basic Logging Functionality
---------------------------

  * ``log`` puts a green asterisk behind the message and terminates its string
    argument with an ellipsis (...). One must follow up ``log`` with one of two
    functions that tag the log message:

    + ``ok`` which indicates successful execution and prints an [  OK  ] tag

    + ``fail`` which indicates unsuccessful execution and prints a [ FAIL ]
      tag 

    One use case of this is to log an attempted action, then try the action 
    in an if-statement; if successful call ok, else fail.

  * ``tip`` puts a blue asterisk behind the message and terminates its string
    argument with an period (.) then automatically prints an [ INFO ] tag in
    blue.

  * ``warn`` puts a yellow asterisk behind the message and terminates its string
    argument with an period (.) then automatically prints an [ WARN ] tag in
    orange.

  * ``die`` puts a red asterisk behind the message and terminates its string
    argument with an period (!) then automatically prints an [ FAIL ] tag in
    red. It terminates the script.


Interactive Input
-----------------

  * ``prompt`` prompts for input, which is then stored in an environment
    variable called ``$REPLY``.

  * ``yesno`` asks a yes/no question and returns true (0 in bash scripts)
    if the user answers yes, false (1 in bash scripts) otherwise


Checking
--------

  * ``check_file`` checks if a file exists. It takes two arguments: the first
    is a description of the file (a one-word adjective), the second is the path
    to the file. These should be in double-quotes.

  * ``check_dir`` checks if a directory exists. It takes two arguments: the
    first is a description of the directory (a one-word adjective), the second is
    the path to the directory.  These should be in double-quotes.

  * ``check_var`` checks if a variable is set. It takes two arguments: the
    first is a description of the variable (a one-word adjective), the second is
    the variable itself.  The arguments should be in double-quotes.

  * ``check_cmd`` checks if a command exists. It takes two arguments: the first
    is a description of the command (a one-word adjective), the second is the
    command itself.  The arguments should be in double-quotes.


Exeuction and Checking
----------------------

  * ``s_exn`` will execute a command and print an ok message if successful,
    otherwise a fail message. It takes two arguments: the first is a log message
    detailing what is being executed, and the second is the command. Both
    arguments should be in double-quotes.

    + It is important to note that by default, in the event of an execution
      failure, the script will stop. One may use ``set +e`` to disable this
      behavior.

  * ``s_ex`` will do the same as ``s_exn`` but will background the process.


Behavior
--------

  * The ``TYPEOUT`` environment variable may be set to ``true`` to cause any
    of the messages to be "typed out", as if by a human; then ``false`` to
    disable this behavior. You can also typeout text with the ``typeout``
    function regardless of whether or not the variable is set.

  * The ``QUIET`` environment variable may be set to ``true`` to cause any
    of the messages to be silent, then set to ``false`` to disable.


How to Use
----------

Note that you must include it using the line

  .. code:: sh

     source '/usr/lib/smartlog/smartlog.sh'

which is used to include its source.


Post-Execution Logs
-------------------

The messages from ``smartlog`` are automatically dumped into .output.log and
.error.log files (hidden in the current directory), in addition to being shown
on stdout.  To view those files, use the ``cat`` command on them; they won't
render correctly in a software like ``vim`` since they contain ANSI color
change escape sequences.


Installing SmartLog on Your System
----------------------------------

If you want for ``smartlog`` to work on your system, then clone it from my
GitHub page (http://github.com/dcastl2/smartlog) and run ``install.sh`` as a
superuser (not via sudo, but as root).
