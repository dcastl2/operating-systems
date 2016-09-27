#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void game() {
  printf("Kitties!\n");
}

int main() {
  srand(time(NULL)+getpid());
  int x = rand()%100;
  if (x == 99) 
    game();
}
