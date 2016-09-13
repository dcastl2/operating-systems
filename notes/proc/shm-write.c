#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

#define SIZE   4096

int main() {

  const char *name    = "box";
  const char *message = "Hello!";
  int   shm_fd;
  void *shm_ptr;

  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, SIZE);
  shm_ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  sprintf(shm_ptr, "%s", message);

  char buffer[256];
  sscanf(shm_ptr, "%s", buffer);
  printf("Written: %s\n", buffer);

  return 0;

}
