#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int nexthex(int fd, char *c) {
  while (read(fd, c, 1)) {
    if (*c == '%') {
      while (read(fd, c, 1))
         if (*c == '\n') break; 
    } else if (isxdigit(*c))
      return 1;
  }
  return 0;
}


char translation(char *C) {
  int i, ascii = 0;
  for (i=0; i<=1; i++) {
    if (isdigit(C[i])) ascii += (C[i] - '0');
    else ascii += (tolower(C[i]) - 'a' + 10);
    ascii *= (i==0) ? 16 : 1;
  }
  return (char) ascii;
}


int main(int argc, char **argv) {
  int fd = open(argv[1], O_RDONLY);
  char C[2];
  while (nexthex(fd, C))
     if (nexthex(fd, C+1)) 
       printf("%c", translation(C));
}
