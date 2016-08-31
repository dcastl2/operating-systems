#include <iostream>
#include <cmath>
#include <algorithm>


// Target:   O(sqrt(n)) time
/* Current:  O(n)       time
 */
bool is_prime(int n) {
  for (int i=2; i<n; i++)
    if (n%i == 0)
      return false;
  return true;
}


// Target:   O(1) additional space
/* Current:  O(n) additional space
 */
std::string reverse(std::string s) {
  std::string c = s;
  for (int i=0; i<s.size(); i++)
    c[i] = s[s.size()-i-1];
  return c;
}


// Target:   O(n)   time
/* Current:  O(n^2) time
 */
int range(int a[], int n) {
  int d = a[n-1]-a[0];
  for (int i=0; i<n; i++)
    for (int j=0; j<i; j++)
      if (std::abs(a[i]-a[j]) > d)
        d = std::abs(a[i]-a[j]);
  return d;
}


// Target:   O(n)        time
/* Current:  O(n*log(n)) time
 */
bool is_sorted(std::string s) {
  std::string c = s;
  std::sort(c.begin(), c.end());
  return (s==c);
}


// Target:   O(log(n))  time
/* Current:  O(n)       time
 */
int search(int a[], int n, int k) {
  for (int i=0; i<n; i++)
    if (a[i] == k)
      return i;
  return -1;
}


int main() {
//int a[5] = {3, 7, 2, 5, 11};
//std::cout << range(a, 5)        << std::endl;
  std::cout << is_sorted("aegis") << std::endl;
}
