#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>


// Print usage message.
void usage(char *name) {
  printf("usage: %s [options]\n\n", name);
  printf("  options:\n");
  printf("    -m, --from\n");
  printf("        start index (default 1)\n\n");
  printf("    -n, --to  \n");
  printf("        end index (default 10)\n\n");
  printf("    -j, --step\n");
  printf("        step size (default 1)\n\n");
  printf("    -v, --verbose\n");
  printf("        verbosity (max -vvv)\n\n");
}


// Return sum from m to n in steps of j. Also print steps of the process, with
// detail depending on the value of the int verbosity.
int sum(int m, int n, int j, int verbosity) {
  int s = 0, k = 1;
  if (verbosity > 2)
   printf("Start: %4d\nStop:  %4d\nStep:  %4d\n", m, n, j);
  if (verbosity > 1)
   printf("Initializing sum to 0.\n");
  for (int i=m; i<=n; i+=j) {
    s += i;
    if (verbosity > 1)
      printf("Iteration %2d:   ", k);
    if (verbosity > 0)
      printf("i = %2d:   s = %4d", i, s); 
    if (verbosity > 2)
      printf("   (let s = %d + %d)", s-i, i); 
    if (verbosity > 0)
      printf("\n");
    k++;
  }
  if (verbosity > 0)
    printf("Final sum: ");
  printf("%d\n", s);
  return s;
}


// Demonstrate getopt_long functionality.
int main(int argc, char **argv) {

  int m=1, n=10, j=1;
  int c, digit_optind = 0, verbosity=0;

  // This struct contains the long options.
  // First  field:  name
  // Second field:  has required argument
  // Third  field:  flag
  // Fourth field:  short option character
  static struct option long_options[] = {
      {"from",     1, 0, 'm'},
      {"to",       1, 0, 'n'},
      {"step",     1, 0, 'j'},
      {"verbose",  0, 0, 'v'},
  };

  // Loop to parse arguments; breaks when no more can be parsed.
  while (1) {

    // Get the option.
    c = getopt_long(argc, argv, "m:n:j:v", long_options, NULL);

    // If option does not exist, break from while-loop.
    if (c == -1)
      break;

    switch (c) {

      case 'm':
        m = atoi(optarg);
        break;

      case 'n':
        n = atoi(optarg);
        break;

      case 'j':
        j = atoi(optarg);
        break;

      case 'v':
        verbosity++;
        break;

      case '?':
        break;

      default:
        usage(argv[0]);
	exit(EXIT_FAILURE);
    }
  }

  // If more CL arguments were passed than the option list allowed,
  // print usage and exit.
  if (optind < argc) {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }

  if (argc == 1) usage(argv[0]);
  else           sum(m, n, j, verbosity);

  exit(EXIT_SUCCESS);

}
