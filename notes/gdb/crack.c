#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void game() {
  printf("Here is a fun game that you cannot play\n");
}

int main(int argc, char **argv) {

  if (argc != 2) {
    fprintf(stderr, "usage: %s password\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (0==strcmp(argv[1], "kitties")) 
    game();
  else {
    fprintf(stderr, "The password was incorrect!\n");
  }

}
