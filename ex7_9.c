#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler(int signo) {
     psignal(signo, "Received Signal");
}
  
int main(void) {
    sigset(SIGALRM, handler);
  
    alarm(2);
    printf("Wait...\n");
    sleep(3);
    //sleep(1);
    return 0;
}