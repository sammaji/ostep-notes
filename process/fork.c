#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  printf(">> current process (pid: %d)\n", (int) getpid());

  int rc = fork();
  if (rc < 0) {
    printf("xx forking failed...\n");
    exit(1);
  }
  else if (rc == 0) {
    printf(">> child process (pid: %d)\n", (int) getpid());

    // testing exec function
    // exec syscall is used to run other command
    // the code below prints out this file
    char *comnd[3];
    comnd[0] = strdup("head");
    comnd[1] = strdup("fork.c");
    comnd[2] = NULL;

    printf(">> command: ");
    for (int i=0; comnd[i] != NULL; i++) {
      printf("%s ", comnd[i]);
    }
    
    printf("\n>> Contents of %s:\n", comnd[1]);
    execvp(comnd[0], comnd);

  } else {
    int rc_wait = wait(NULL); // waits for child process to run
    printf(">> parent process (pid: %d) (rc: %d) (rc_wait: %d)\n", (int) getpid(), rc, rc_wait);
    
  }

  return 0;
}
