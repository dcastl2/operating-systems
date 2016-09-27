#include <pthread.h>
#include <stdio.h>

int f;

void *runner(void *param) {
  int i, *n = param;
  f = 1;
  for (i=1; i<=*n; i++)
    f *= i;
  pthread_exit(0); 
}


int main() {

  int value[1] = {10};

  pthread_attr_t attr;
  pthread_attr_init(&attr);

  pthread_t tid;
  pthread_create(&tid, &attr, runner, value);
  pthread_join(tid, NULL);

  printf("10! = %d\n", f);

}
