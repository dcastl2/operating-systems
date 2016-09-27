#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void game() {
  printf("Kitties!\n");
}

int sum(int n) {
  int i, s = 0;
  for (i=0; i<=n; i++) 
    s += 0;
  return s;
}

int main(int argc, char **argv) {
  assert(argc == 2);
  if (sum(atoi(argv[1])) == 56)
    game();
}
