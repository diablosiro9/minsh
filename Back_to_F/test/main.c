#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int pid = fork();
  if (pid == 0) {
    // child process
    execlp("ls", "-l", (char*)NULL);
    // if execlp returns, it means there was an error
    perror("execlp");
    exit(1);
  } else if (pid > 0) {
    // parent process
    int status;
    waitpid(pid, &status, 0);
    printf("child process finished with status %d\n", status);
  } else {
    // fork failed
    perror("fork");
    exit(1);
  }
  return 0;
}
