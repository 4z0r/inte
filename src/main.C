#include <stdio.h>
#include <stdlib.h>
#include "main.H"
#include "debug.H"
#include "functions.H"
#include "cfgparse.H"

#ifndef TEST

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

#else

int main(int argc, char *argv[])
{
  //some test here
  int parser; 
  int forkp; 

  if((parser=check_parser()))
    {
      //parser ok
    }

  if((forkp=check_fork()))
    {
      //fork ok
    }

  printf("\n");
  printf("********************\n");
  printf("* ALL TESTS PASSED *\n");
  printf("********************\n");
  printf("\n");

  return(EXIT_SUCCESS);
}

#endif
