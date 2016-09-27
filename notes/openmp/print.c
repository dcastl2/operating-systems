#include <stdio.h>

#define N 16

int main() {

  int i;

  #pragma omp parallel for num_threads(4)
  for (i=0; i<=N; i++) {
      printf("%d\n", i);
  }

}
