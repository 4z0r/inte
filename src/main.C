#include <stdio.h>
#include <stdlib.h>
#include "main.H"
#include "debug.H"
#include "functions.H"

int main(int argc, char *argv[], char *envp[])
{
  char *input = (char*) malloc(256);

  printf("%s ", SHELL_CHARACTER);

  while(fscanf(stdin, "%s", input) == 1)
    {
      //quit 
      if(!strcmp(input, "quit")
	 || !strcmp(input, "exit")
	 || !strcmp(input, "q"))
	{
	  break;
	}

      //help
      else if(!strcmp(input, "help"))
	{
	  printf("Print the help.\n");
	}

      //unknown
      else
	{
	  printf("[INFO] Command %s unknown.\n", input);
	}
      printf("%s ", SHELL_CHARACTER);
    }
  
  if(input) free(input);
  
  printf("Good Bye!\n");

  return(EXIT_SUCCESS);
}
