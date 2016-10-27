#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <crypt.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

void ith(char *password, int index, int n) {
  for (int i=1; i<=n; i++) {
    password[i-1] = (index % 26) + 'a';
    index /= 26;
  }
  password[n] = '\0';
}


int main() {

  char *hash;
  char target[16];
  char password[5];
  char salt[3];

  int N=pow(26, 4);
  int M=pow(26, 2);

  int fd  = open("hash", 'r');
  int num = read(fd, target, 16);
  if (num) target[num-1] = 0;
  else     exit(0);
  close(fd);

  for (int i=0; i<N; i++) {
    ith(password, i, 4);
    for (int j=0; j<M; j++) {
      ith(salt,     j, 2);
      hash = crypt(password, salt);
      if (0==strcmp(hash, target)) {
        printf("Password: %s\t\tSalt: %s\t\tHash: %s\t\tTarget: %s\n", password, salt, hash, target);
        exit(1);
      } else printf("Trying %s...\r", password);
    }
  }

}
