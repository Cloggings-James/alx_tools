#include <stdio.h>
#include "functions.h"
#include <string.h>
int main() {
  char input[100];

  while(1) {
    printf("myshell> ");
    scanf("%s", input);  
    
    if(!strcmp(input, "ls")) {
      ls();    
    } 
    else if(!strcmp(input, "exit")) {
      exit(0);
    }
  }
  
  return 0;
}
