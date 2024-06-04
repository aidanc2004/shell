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

void execute_command(char *command, char *args[]) {
  // Skip if command is "cd"
  if (strncmp(command, "cd", BUFFER_SIZE) == 0) return;
  
  execvp(command, args);
}

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

    // Split input into arguments
    char *tok = strtok(buffer, " ");
    while (tok != NULL) {
      // Set first argument to the command
      if (args_i == 0) command = tok;
      
      args[args_i] = tok;

      tok = strtok(NULL, " "); // Next token

      args_i++;
    }

    args[args_i] = NULL; // Last element to NULL

    // 'cd' command, needs to be done before forking
    if (strncmp(command, "cd", BUFFER_SIZE) == 0) {
      int res = chdir(args[1]);
      // Check for an error
      if (res != 0) {
        fprintf(stderr, "Err: Directory %s not found.\n", args[1]);
      }
    }
    
    // Create child to exec command
    pid_t pid = fork();
    if (pid == 0) {
      execute_command(command, args);
    }

    // Wait for current exec call to finish
    wait(NULL);
  }

  return 0;
}
