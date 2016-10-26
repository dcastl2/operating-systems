#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


/*
 * Here is a global variable which is used to flag for continuation
 * of a loop, shown below in main().
 */
int cont = 1;


/*
 * This is a handler function which catches the signal and decides
 * what to do with it.
 */
void alarm_handler(int signal) {
  cont = 0;
}


int main() {

  /**
   * The signal() function ties a certain signal to a handler. This
   * particular call associates an alarm signal with the function
   * defined above.  The alarm() call indicates that a SIGALRM is
   * to be sent to the current executable in 3 seconds.  At that
   * point, the signal will be handled by the handler defined above.
   */
  signal(SIGALRM, alarm_handler);
  alarm(3);
  
  /**
   * This loop will meow as long as cont is set to true.  It is set
   * to false in the handler; thus when the alarm goes off, it should
   * trigger the exit of the loop.
   */
  while (cont) {
    printf("Meow ");
    fflush(stdout);
    usleep(500000);
  }

  /**
   * When the meowing loop ends, a hiss is printed to indicate the
   * break from the loop.
   */
  printf("*Hiss*\n");
  return 0;

}
