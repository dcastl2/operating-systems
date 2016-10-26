#include <sys/types.h>
#include <signal.h>

/**
 * This program raises a segmentation fault signal, thus it will print
 * the classic "Segmentation fault" message even though there is no
 * segmentation fault.
 */
int main() {
  raise(SIGSEGV);
}
