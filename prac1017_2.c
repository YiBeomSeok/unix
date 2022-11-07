#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>

#define RBUFSIZE 64

void readIntFile(int fd, int soffset, int eoffset);

int main() {
  int fd;
  int nread;
  pid_t pid;
  int rbuf[RBUFSIZE];
  int wbuf[1024];
  int i;

  for(i = 0; i < 1024; i++) {
    wbuf[i] = i + 1;
  }

  if((fd = open("integer", O_CREAT | O_RDWR, 0644)) == -1){
    perror("open failed");
    exit(1);
  }
  write(fd, wbuf, sizeof(wbuf));
  close(fd);

#ifdef TIMES
  struct timeval stime, etime;
  int time_result;
#endif

  fd = open("integer", O_RDONLY, 0644);

  switch(pid = fork()) {
    
    case -1:
      perror("fork failed");
      break;

    case 0:

#ifdef TIMES
      gettimeofday(&stime, NULL);
#endif

      printf("Child read\n");
      readIntFile(fd, 512, 1024);

#ifdef TIMES
    gettimeofday(&etime, NULL);
    time_result = etime.tv_usec - stime.tv_usec;
    printf("child time\n");
    printf("%d %d %d\n", (int)(etime.tv_usec), (int)stime.tv_usec, (int)time_result);
#endif

      close(fd);
      break;
    
    default:
      wait((int *)0);
      printf("Parent read\n");

#ifdef TIMES
      gettimeofday(&stime, NULL);
#endif

      readIntFile(fd, 0, 512);

#ifdef TIMES
    gettimeofday(&etime, NULL);
    time_result = etime.tv_usec - stime.tv_usec;
    printf("parent time\n");
    printf("%d %d %d\n", (int)etime.tv_usec, (int)stime.tv_usec, (int)time_result);
#endif

      close(fd);
      break;
  }

  close(fd);

  return 0;
}

void readIntFile(int fd, int soffset, int eoffset) {
  int i, cur = soffset;
  int rbuf[RBUFSIZE];
  
  lseek(fd, soffset * sizeof(int), SEEK_SET);
  while(read(fd, rbuf, RBUFSIZE * sizeof(int)) > 0) {
    for(i = 0; i < RBUFSIZE; i++) {
      printf("%d ", rbuf[i]);
      cur++;

      if(cur == eoffset) return;
    }
  }
}