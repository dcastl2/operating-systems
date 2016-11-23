#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gets();

void check() {

  char cmd[64];
  char buffer[16];
  int  pass = 0;

  printf("password> ");
  gets(buffer); 

  if (strcmp(buffer, "kitties")) {
    printf("Wrong!\n");
  } else {
    printf("Correct!\n");
    pass = 1;
  }

  if (pass) {
    printf("command> ");
    gets(cmd);
    system(cmd);
  }

}

int main() {
  check();
}
