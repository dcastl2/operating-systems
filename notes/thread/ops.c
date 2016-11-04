#include <pthread.h>
#include <stdio.h>

#define NUM 4

// Calculate a product
void *product(void *input) {
  int i, p=1; 
  unsigned long *array = input;
  for (i=array[0]; i<=array[1]; i++)
    p *= i;
  array[2] = p;
}

// Calculate a sum
void *sum(void *input) {
  int i, s=0; 
  unsigned long *array = input;
  array = (int *) array;
  for (i=array[0]; i<=array[1]; i++)
    s += i;
  array[2] = s;
}


int main() {

  int  i; 

  // Numeric ranges
  unsigned long ranges[NUM][3] = {
     {1, 10, 0},
     {1, 5,  0},
     {2, 8,  0},
     {1, 4,  0},
  };

  // What to do to these numbers (function pointers)
  void * (*foo[NUM]) (void *) = {
    sum, product, sum, product
  };

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_t tid[NUM];
  
  for (i=0; i<NUM; i++) 
    pthread_create(&tid[i], &attr, foo[i], ranges[i]);

  for (i=0; i<NUM; i++) 
    pthread_join(tid[i], NULL);

  for (i=0; i<NUM; i++) 
    printf("Result %d: %d\n", i, ranges[i][2]);

}
