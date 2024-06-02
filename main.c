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

    char *args[BUFFER_SIZE] = {NULL};
    int args_i = 0;

    char *command;

    //char *tok;
    char *tok = strtok(buffer, " ");
    
    while (tok != NULL) {
      // Set first argument to the command
      if (args_i == 0) command = tok;
      
      args[args_i] = tok;

      tok = strtok(NULL, " "); // Next token

      args_i++;
    }

    args[args_i] = NULL;
    
    // Create child to exec command
    pid_t pid = fork();
    if (pid == 0) {
      execvp(command, args);
    }

    // Wait for current exec call to finish
    wait(NULL);
  }

  return 0;
}
