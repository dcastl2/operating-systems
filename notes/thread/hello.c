#include <pthread.h>
#include <stdio.h>

#define NUM 4

void *hello(void *param) {
  printf("Hello, world!\n");
}


int main() {

  int  i; 

  // Give the threads the default attributes.
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  // Need separate threads for each running process.
  pthread_t tid[NUM];
  
  // Create the threads and run the process.
  for (i=0; i<NUM; i++) {
    //printf("Creating thread %d...\n", i);
    pthread_create(&tid[i], &attr, hello, NULL);
  }

  // Join threads with the current process (wait for them to finish).
  for (i=0; i<NUM; i++) {
    //printf("Joining thread %d...\n", i);
    pthread_join(tid[i], NULL);
  }

  printf("Finished!\n");

}
