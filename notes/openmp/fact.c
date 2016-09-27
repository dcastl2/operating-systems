#include <stdio.h>

#define N 10

int main() {

  int i, product=1;

  #pragma omp parallel for reduction(*:product)
  for (i=1; i<=N; i++) {
      product = product * i;
  }

  printf("Result: %d\n", product);

}
