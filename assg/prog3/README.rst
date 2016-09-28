Homework 3
==========

Select up to 64 points worth of problems.  You may earn +N extra credit points
if you submit the assignment N<=8 days in advance of the due date (Sunday at
6:00:00 PM on 10/09/2016).


1. IP geolocation.
     [16] Write a script to trace the geolocations of hops to the IP addresses
     of everyone logged on to the server.  For each IP address of everyone who
     is logged in to the server (use ``w -i`` and ``awk`` to isolate the IP
     addresses),  run a traceroute to track hops to the IP address (use
     ``traceroute``), and obtain the GPS coordinates of each hop (use ``curl``
     to query the ``ipinfo.io`` database).  Print also the GPS coordinates of
     the IP.  Account for the fact that the traceroute may time out.  Format
     your output neatly. Call this ``trace.sh``.


2. A foolproof progress bar.
     [16] Using an ``ioctl()`` call to find the exact width of the terminal,
     write a program with function ``void bar(float percent)`` which can print
     out a progress bar given ``percent`` as an argument.  It should work for a
     terminal of any width; and in fact should update correctly if the width of
     the terminal is changed mid-execution.  An example executable ``bar`` is
     provided.  Call this ``bar.c``.  See the ``ioctl`` and ``ioctl_list``
     manual pages for clues on how to call ``ioctl()``.


3. A port scanner.
     [16] Write a sockets program which accepts an IP address as a command-line
     argument, then scans ports 21, 22, 23, 25, 80, 143, 443, and 993 to see if
     they accept connections.  On a successful connection, close the connection
     then print out the port.  Call this ``scan.c``.  You will need to set an
     options for connection timeout to make the port scanner feasible to use
     on remote hosts. 


4. Approximating pi.
     [16] Write a program using pthreads which approximates pi using the Monte
     Carlo technique.  In this technique, a unit circle (of area pi) is
     circumscribed inside a square (of area 4).  Random numbers are generated
     within the square.  The number which fall inside the circle (c) is
     counted, and divided by the total generated (t).  For large t, c/t
     approximates pi/4.  
     
     Write a multi-threaded program (using the C pthread library) which creates
     four threads to independently approximate pi using this technique; then
     average the results.  Use t=10000 for each thread.  Call this ``pi.c``.
     Note that you will need to link against the pthreads library when
     compiling.


5. Calculating the dot product.
     [16] Write a multi-threaded program using pthreads which calculates the
     dot product of two arrays *u* and *v*. To do this, split each of the
     arrays in half, calculate the dot products of the two halves, then add the
     results together.  Create two threads to achieve this end. Assume that the
     sizes of *u* and *v* are even.  Call it ``dot.c``.  In your output, show
     the two arrays *u* and *v* and the final result of the dot product.


6. Calculating sine.
     [16]. Using OpenMP, write a program which accepts a floating-point number
     as a command-line argument then calculates the sine, cosine, and tangent
     of the number.  Write the function ``double sin(double x)`` which
     calculates the sine of a given argument ``x`` in parallel using the Taylor
     series formula for the sine function.  Obtain the cosine and tangent using
     trigonometric identities.  Output the results.  Call this ``sine.c``.


7. Sums and products.
     [16]. Using OpenMP, write a program which accepts integer start, stop, and
     step values (in that order) as command-line arguments and calculates in
     parallel both the sum and product from start to stop (inclusive) in
     increments of step.  Be sure to use the proper reductions, and check to
     be sure that the results are correct.  Call this ``sigma.c``.
