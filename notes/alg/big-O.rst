Algorithms
==========

We can think of an **algorithm** as an unambiguous procedure for solving a
problem.  All algorithms can be thought of as the sequence of intermediate
steps required to obtain a desired output given an input.

                   +-------------------------------+
                   | Input -> Algorithm -> Output  |
                   +-------------------------------+

Consider, for example, summing numbers from 1 to n.  The number n is the
input, the sum is the output, and the algorithm is the sequence of steps
required to obtain the sum.  But there are many ways to obtain the sum;
one is to add up all the numbers, which takes n operations.  Another is 
to calculate it directly, which always takes 3 operations regardless of
how big n is.


The Big-O Notation
==================

The **time complexity** of an algorithm or program is the amount of operations
it takes for the algorithm to run.  Typically time complexity is expressed in
terms of the **big-O**.  Given an input size n, the big-O tells roughly how
many operations are required in terms of n.

For example, consider the following sum code.  It takes n operations for this
code to find the sum, since it has to iterate over all the numbers from 1 to n.
We say that the time complexity of this code is O(n).

.. code:: cpp

     int sum(int n) {
       int s = 0;
       for (int i=1; i<=n; i++)
         s += i;
       return s;
     }

Contrast that with the following sum code, which uses a formula to calculate
the sum of numbers. It only requires 3 operations (this is comparable to 1
operation).  The number of operations does not depend on n, so we say that the
time complexity of this code is O(1).

.. code:: cpp

     int sum(int n) {
       return (n*(n+1))/2;
     }

We say that the O(1) sum code is more **time efficient** than the O(n) code.
An O(n) code is more time efficient than an O(n^2) code, and so forth.
Typically, when we report the big-O, we report the highest-order polynomial for
the total number of operations.  If a code requires n^2 + n operations, it is
O(n^2).  If it requires n + 4 operations, it is O(n).

If a code depends on more than one input, then we include that input as well.
For example, calculating the sum of an n-by-m matrix would require O(nm) time.
Calculating the sum of a size-n array and a size-m array and adding them
together would require O(n+m) time.
