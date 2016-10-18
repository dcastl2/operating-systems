#include <pthread.h>
#include <stdio.h>

int main() {

  pthread_mutex_t mutex;
  pthread_mutex_init(&mutex, NULL);

  pthread_mutex_lock(&mutex);
  if (pthread_mutex_trylock(&mutex))
       printf("Locked!\n");
  else printf("Unlocked!\n");
  pthread_mutex_unlock(&mutex);

}
