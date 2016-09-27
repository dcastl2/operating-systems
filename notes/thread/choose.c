#include <pthread.h>
#include <stdio.h>

#define NUM 2

// Calculates product from a to b.  The function takes in a void pointer,
// which can refer to anything.  Since it is a pointer, if we change its
// values, they will stay when we return from the running thread.
//
// To calculate a product, we create a matrix (which is a double pointer)
// then for each thread, pass in a row of the matrix.  Each row has three
// elements.  The first is a, the lower limit; the second is b, the upper
// limit; and the third is to hold the result of the calculation once the
// thread is finished.
void *product(void *param) {
  int  i; 
  unsigned long f = 1;
  unsigned long *vals = param;
  for (i=vals[0]; i<=vals[1]; i++)
    f *= i;
  vals[2] = f;
}


int main() {

  int  i; 

  // Use an array to hold the ranges the product will cover
  // and the final result of each calculation.
  unsigned long ranges[NUM][3] = {
     {47, 52,  0},
     {1,   5,  0}
  };

  // Give the threads the default attributes.
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  // Need separate threads for each running process.
  pthread_t tid[2];
  
  // Create the threads and run the process.
  for (i=0; i<NUM; i++) 
    pthread_create(&tid[i], &attr, product, ranges[i]);

  // Join threads with the current process (wait for them to finish).
  for (i=0; i<NUM; i++) 
    pthread_join(tid[i], NULL);

  // Print the results.
  for (i=0; i<NUM; i++) 
    printf("Result %d: %lu\n", i, ranges[i][2]);

  // Print the final result.
  printf("Final result: %lu\n", ranges[0][2]/ranges[1][2]);

}
