#include <iostream>
#include <iomanip>

/**
 * Sum numbers from 1 to n in O(n) time, return # operations.
 * @param n  number to sum up to
 * @return   number of operations taken
 */
int inefficient_sum(int n) {
  int s = 0, ops = 0;
  for (int i=1; i<=n; i++) {
    s += i;
    ops++;
  }
  return ops;
}

/**
 * Get # operations for producing multiplication table.
 * @param n  number to produce nxn table for
 * @return   number of operations taken
 */
int multi_table(int n) {
  int ops = 0;
  for (int i=1; i<=n; i++) {
    for (int j=1; j<=n; j++) {
      //std::cout << std::setw(4) << i*j;
      ops++;
    }
    //std::cout << std::endl;
  }
  return ops;
}



int main() {

  std::cout << "For calculating the sum in O(n) time: " << std::endl;
  std::cout << "i" << std::setw(8) << "ops" << std::endl;
  for (int i=0; i<=10; i++) 
    std::cout << i << std::setw(8) << inefficient_sum(i) << std::endl;
  std::cout << std::endl;

  std::cout << "For producing a multiplication table in O(n^2) time: " << std::endl;
  std::cout << "i" << std::setw(8) << "ops" << std::endl;
  for (int i=0; i<=10; i++) 
    std::cout << i << std::setw(8) << multi_table(i) << std::endl;


}
