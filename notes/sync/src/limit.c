#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define NUM 10

sem_t sem;
int love = 1;

void *snuggle(void *input) {
  pthread_t *id = input;
  sem_trywait(&sem);
  love *= 2;
  printf("<3: %d\n", love);
  sem_post(&sem);
}


int main() {

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_t tid[NUM];

  // Three threads at a time
  sem_init(&sem, 0, 3);

  int i;
  for (i=0; i<NUM; i++) 
    pthread_create(&tid[i], &attr, snuggle, &i);
  for (i=0; i<NUM; i++) 
    pthread_join(tid[i], NULL);
  printf("Final value: %d\n", love);

}
