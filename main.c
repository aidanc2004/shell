/*
 * Aidan Carey
 * June 1st 2024
 * main.c
 */

#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"

int main() {
  char *args[] = {"-a", NULL};
  
  pid_t pid = fork();
  if (pid == 0) {
    execvp("ls", args);
  }

  wait(NULL);

  printf("done!\n");

  return 0;
}
