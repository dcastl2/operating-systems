#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 1024
#define READ  0
#define WRITE 1

int main() {

  char  parent_message[SIZE] = "Hello!"; 
  char  child_message[SIZE];
  int   fd[2];
  pid_t pid;
  
  if (-1 == pipe(fd)) {
    fprintf(stderr, "Pipe failed\n");
    exit(EXIT_FAILURE);
  }

  pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Pipe failed\n");
    exit(EXIT_FAILURE);
  }

  else if (pid == 0) {
    close(fd[READ]);
    write(fd[WRITE], parent_message, strlen(parent_message)+1);
    printf("Write: %s\n", parent_message);
    close(fd[WRITE]);
  }

  else {
    close(fd[WRITE]);
    read(fd[READ], child_message, SIZE);
    close(fd[READ]);
    printf("Read:  %s\n", child_message, SIZE);
  }

  return 0;

}
