/*
 * Aidan Carey
 * June 1st 2024
 * main.c
 */

#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/wait.h"

#define BUFFER_SIZE 256

int main() {
  char buffer[BUFFER_SIZE] = {};

  while (1) {
    // Prompt
    printf("> ");
    
    // TODO: Replace scanf with sscanf
    scanf("%s", buffer);

    char *args[] = {NULL};
    
    // Create child
    pid_t pid = fork();
    if (pid == 0) {
      execvp(buffer, args);
    }

    wait(NULL);
  }

  return 0;
}
