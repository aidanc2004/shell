/*
 * Aidan Carey
 * June 1st 2024
 * main.c
 */

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "sys/types.h"
#include "sys/wait.h"

#define BUFFER_SIZE 256

int main() {
  char buffer[BUFFER_SIZE] = {};

  while (1) {
    // Prompt
    printf("> ");
    
    // Get user input
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
      fprintf(stderr, "Couldn't get input.\n");
      exit(-1);
    }
    
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline
    
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
