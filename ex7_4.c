#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signo) {
  printf("Signal Handler Signal Number : %d\n", signo);
  psignal(signo, "Received Signal");
}

int main() {

#if 0
  if(sigset(SIGINT, handler) == SIG_ERR) {
    perror("sigset");
    exit(1);
  }
#endif

  printf("Wait 1st Ctrl+c... : SIGINT\n");
  pause();

  printf("After 1st Signal Handler\n");
  printf("Wait 2nd Ctrl+c... : SIGINT\n");
  pause();
  printf("After 2nd Signal Handler\n");

  return 0;
}