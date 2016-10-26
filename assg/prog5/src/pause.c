#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void usage(char *progname) {
  printf("usage: %s pid seconds\n", progname);
}

void alarm_handler(int signal) {
  exit(1);
}


int main(int argc, char **argv) {

  /**
   * First argument is the PID of the process, the second is the amount
   * of seconds to pause it for.
   */
  if (argc != 3) {
    usage(argv[0]);
    exit(0);
  }
  int pid     = atoi(argv[1]);
  int naptime = atoi(argv[2]);

  /**
   * To achieve the effect, we send two signals via kill().  One is
   * SIGSTOP, which pauses the process, then later SIGCONT, which
   * continues it.
   */
  printf("Stopping %d... ", pid);
  fflush(stdout);
  kill(pid, SIGSTOP);
  sleep(naptime);
  printf("Restarting %d... ", pid);
  fflush(stdout);
  kill(pid, SIGCONT);

}
