#include <iostream>

/**
 * Sum numbers from 1 to n in O(n) time.
 * @param n  number to sum up to
 * @return   sum of numbers
 */
int inefficient_sum(int n) {
  int s = 0;
  for (int i=1; i<=n; i++) 
    s += i;
  return s;
}

/**
 * Sum numbers from 1 to n in O(1) time.
 * @param n  number to sum up to
 * @return   sum of numbers
 */
int efficient_sum(int n) {
  return (n*(n+1))/2;
}

int main() {
  std::cout << inefficient_sum(10) << std::endl;
  std::cout <<   efficient_sum(10) << std::endl;
}
