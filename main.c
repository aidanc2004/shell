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

int main(void) {
  char buffer[BUFFER_SIZE] = {0};

  while (1) {
    // Prompt
    char cwd[BUFFER_SIZE] = "";
    getcwd(cwd, BUFFER_SIZE);
    
    printf("%s $ ", cwd);
    
    // Get user input
    if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
      fprintf(stderr, "Couldn't get input.\n");
      exit(-1);
    }
    
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline

    // TODO: Split string by space

    char *args[] = {NULL};
    
    // TODO: Add all strings except first to args
    
    // Create child to exec command
    pid_t pid = fork();
    if (pid == 0) {
      execvp(buffer, args);
    }

    // Wait for current exec call to finish
    wait(NULL);
  }

  return 0;
}
