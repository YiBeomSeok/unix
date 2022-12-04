#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

void handler(int signo) {
}

int main() {
  int shmid;
  int pid;
  sigset_t set;
  char* shmaddr;
  char buf[80];
  
  shmid = shmget(10386, 1024, IPC_CREAT|0644);
  if(shmid == -1) {
    perror("shmget");
    exit(1);
  }
  
  sigfillset(&set);
  sigdelset(&set, SIGUSR1);
  sigset(SIGUSR1, handler);
  sigsuspend(&set);

  shmaddr = (char *)shmat(shmid, (char *)NULL, 0);
  printf("[SERVER] client PID = %s\n", shmaddr);
  pid = atoi(shmaddr);
  strcpy(shmaddr, "통신을 시작합니다.\n");
  kill(pid, SIGUSR1);

  while(1) {
    sigsuspend(&set);
    shmaddr = shmat(shmid, NULL, 0);
    strcpy(buf, shmaddr);
    printf("[SERVER] received : %s", buf);
    if(buf[0] == 'q') break;

    printf("[SERVER] Input Message: ");
    fgets(buf, 80, stdin);
    strcpy(shmaddr, buf);
    kill(pid, SIGUSR1);
    if(buf[0] == 'q') break;
  }

  shmdt(shmaddr);
  shmctl(shmid, IPC_RMID, NULL);

  return 0;
}