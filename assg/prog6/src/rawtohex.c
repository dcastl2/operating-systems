#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {

  int i=1, fd = open(argv[1], O_RDONLY);
  char c[1];

  while (read(fd, c, 1)) {
       printf("%2.2x ", *c & 0xFF);
       if (i++ % 8 == 0)
         printf("\n");
  }
  printf("\n");

}
