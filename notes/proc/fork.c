#include <stdio.h>
#include <unistd.h>

int main() {

  int p_id = fork();

  // If the PID is negative, this indicates an error code from
  // fork(); there was an issue forking.
  if (p_id < 0) {
    printf("Error forking\n");
  } 
  // If the PID is positive, then this process is the parent
  // process.
  else if (p_id > 0) {
    printf("[%d] Child process\n", p_id);
    execlp("/bin/ls", "ls", NULL);
  } 
  // Otherwise the PID is 0, then this is the child process.
  // It should wait for the child to finish executing.
  else {
    wait(NULL);
    printf("[%d] Parent process\n", p_id);
  }

}
