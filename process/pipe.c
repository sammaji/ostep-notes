#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    printf("xx forking failed...\n");
    exit(1);
  }
  else if (rc == 0) {
    printf(">> child process (pid: %d)\n", (int) getpid());

    close(STDOUT_FILENO);
    open("./pipe.c.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    char *comnd[3];
    comnd[0] = strdup("wc");
    comnd[1] = strdup("fork.c");
    comnd[2] = NULL;

    execvp(comnd[0], comnd);
  }
  else {
    int rc_wait = wait(NULL);
    printf(">> parent process (pid: %d)\n", rc);
  }
}
