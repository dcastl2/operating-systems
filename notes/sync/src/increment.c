#include <pthread.h>
#include <stdio.h>

#define NUM 10

pthread_mutex_t mutex;
int love = 0;

void *cuddle(void *input) {
  pthread_t *id = input;
  while (pthread_mutex_trylock(&mutex));
  love++;
  printf("<3: %d\n", love);
  pthread_mutex_unlock(&mutex);
}


int main() {

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_t tid[NUM];
  pthread_mutex_init(&mutex, NULL);

  int i;
  for (i=0; i<NUM; i++) 
    pthread_create(&tid[i], &attr, cuddle, &i);
  for (i=0; i<NUM; i++) 
    pthread_join(tid[i], NULL);
  printf("Final value: %d\n", love);

}
