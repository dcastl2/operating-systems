I wrote a library for better logging functionality in BaSH scripts. It allows
the user to output log messages similar to kernel output messages, complete
with color-coding and tags indicating the type of message.

Its intended use was to document scripts both internally and during run-time,
so that a user would know exactly where the script failed.  Its core functions:


* ``log`` puts a green sticker behind the message and terminates its string
  argument with an ellipsis (...). One must follow up ``log`` with one of
  two functions that tag the log message:

  + ``ok`` which indicates successful execution and prints an [  OK  ] tag

  + ``fail`` which indicates unsuccessful execution and prints a [ FAIL ]
  tag 

* ``tip`` puts a blue asterisk behind the message and terminates its string
  argument with an period (.) then automatically prints an [ INFO ] tag in
  blue.

* ``warn`` puts a yellow asterisk behind the message and terminates its string
  argument with an period (.) then automatically prints an [ WARN ] tag in
  orange.

* ``die`` puts a red asterisk behind the message and terminates its string
  argument with an period (!) then automatically prints an [ FAIL ] tag in
  red. It terminates the script.

* The ``TYPEOUT`` environment variable may be set to ``true`` to cause any
  of the messages to be "typed out", as if by a human; then ``false`` to
  disable this behavior.


Note that you must include it using the line

  .. code:: sh

     source '/usr/lib/smartlog/smartlog.sh'

which is used to include its source.

The messages from ``smartlog`` are automatically dumped into .output.log and
.error.log files (hidden in the current directory), in addition to being shown
on stdout.  To view those files, use the ``cat`` command on them; they won't
render correctly in a software like ``vim`` since they contain ANSI color
change escape sequences.

If you want for ``smartlog`` to work on your system, then clone it from my
GitHub page (http://github.com/dcastl2/smartlog) and run ``install.sh`` as a
superuser (not via sudo, but as root).
