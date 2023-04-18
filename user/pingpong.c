#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main (int argc, char *argv[]){
  int p[2];
  pipe(p);
  int pid = 0;

  // child
  if (fork() == 0) {
    close(p[0]);
    pid = getpid();
    printf("%d: received ping\n", pid);
    char byte;
    write(p[1], &byte, 1);
    close(p[1]);

  // father
  } else {
    close(p[1]);
    char recv;
    read(p[0], &recv, 1);
    close(p[0]);
    pid = getpid();
    printf("%d: received pong\n", pid);
  }
  exit(0);
}


