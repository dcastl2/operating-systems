#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 1024
#define READ  0
#define WRITE 1

int sum(int a, int b) {
  int i, s=0;
  for (i=a; i<=b; i++)
    s += i;
  return s;
}

int main() {

  int   parent_result; 
  int   child_result;
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
    child_result = sum(1, 500);
    write(fd[WRITE], &child_result, sizeof(int));
    printf("Child sum (1-500):      %d\n", child_result);
    close(fd[WRITE]);
  }

  else {
    close(fd[WRITE]);
    parent_result = sum(501, 1000);
    printf("Parent sum (501-1000):  %d\n", parent_result);
    wait(NULL);
    read(fd[READ], &child_result, sizeof(int));
    printf("Got child sum:          %d\n", child_result);
    close(fd[READ]);
    printf("Total:                  %d\n", parent_result+child_result);
  }

  return 0;

}
