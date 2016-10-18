#include <semaphore.h>
#include <stdio.h>

int main() {

  // Semaphore can only be shared by threads belonging to process
  // which created the semaphore.
  int value;
  sem_t sem;
  sem_init(&sem, 0, 1);

  // Initial value 1
  printf("%d\n", sem);

  // Wait brings to 0
  sem_wait(&sem);
  printf("%d\n", sem);

  // Post brings to 1
  sem_post(&sem);
  printf("%d\n", sem);

  // Wait until non-negative
  sem_trywait(&sem);
  printf("%d\n", sem);

  sem_destroy(&sem);

}
