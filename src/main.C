#include <stdio.h>
#include <stdlib.h>
#include "main.H"
#include "debug.H"
#include "functions.H"
#include "cfgparse.H"

#ifndef TEST

int main(int argc, char *argv[], char *envp[])
{
  cut_line('=');
  printf("%s", welcome_message);
  cut_line('+');

  check_directories_and_files();

  char *input = (char*) malloc(256);
  
  printf("Starting the prompt...\n\n");
  
  printf("prompt%s ", SHELL_CHARACTER);

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
	  printf("\n[INFO] Command %s unknown.\n", input);
	}
      printf("prompt%s ", SHELL_CHARACTER);
    }
  
  if(input) free(input);
  
  printf("\n");
  cut_line('+');
  printf("Good Bye!\n");
  cut_line('=');

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
