#include <iostream>
#include <iomanip>


/**
 * Return the number passed in as an argument.
 * Time  complexity: TODO
 * Space complexity: TODO
 * @param n  number
 * @return   number passed as param
 */
int identity(int n) {
  return n;
}


/**
 * Sum an array of integers.
 * Time  complexity: TODO
 * Space complexity: TODO
 * @param  a  an array of numbers
 * @param  n  the size of the array
 * @return    the sum of the array.
 */
int sum(int a[], int n) {
  int s = 0;
  for (int i=0; i<n; i++)
    s += a[i];
  return s;
}


/**
 * Print array of integers.
 * Time  complexity: TODO
 * Space complexity: TODO
 * @param  a  an array of numbers
 * @param  n  the size of the array
 */
void print(int a[], int n) {
  for (int i=0; i<n; i++)
    std::cout << std::setw(4) << a[i];
  std::cout << std::endl;
}



/**
 * Bubble sort an array of integers.
 * Time  complexity: TODO
 * Space complexity: TODO
 * @param  a  an array of numbers
 * @param  n  the size of the array
 */
void bubble(int a[], int n) {
  for (int i=0; i<n; i++)
    for (int j=0; j<i; j++)
      if (a[i] < a[j])
        std::swap(a[i], a[j]);
}


/**
 * Find the base-2 logarithm of n.
 * Time  complexity: TODO
 * Space complexity: TODO
 * @param  n  the size of the array
 * @return    the base-2 logarithm of n
 */
int log2(int n) {
  int i = 0;
  while (n > 0) {
    n /= 2;
    i++;
  }
  return i;
}


int main() {
  int n = 5;
  int a[n] = {7, 2, 5, 3, 11};
  std::cout << identity(n) << std::endl;
  std::cout << sum(a, n)   << std::endl;
  std::cout << log2(n)     << std::endl;
  bubble(a, n);
  print(a, n);
}
