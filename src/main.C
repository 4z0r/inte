#include <stdio.h>
#include <stdlib.h>
#include "main.H"
#include "functions.H"
#include "cfgparse.H"

#ifdef COLORS
#include "colors_debug.H"
#else
#include "debug.H"
#endif

#ifndef TEST

int main(int argc, char *argv[], char *envp[])
{
  cut_line('=');
  printf("%s", welcome_message);
  char *tmp = prep_output("Ovidiu - Dan Bogat", "blue");
  printf("\n%s\n", tmp);
  free(tmp);
  cut_line('+');

  check_directories_and_files();

  char *input = (char*) malloc(sizeof(char) * 256);
  
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

      //color support info
      else if(!strcmp(input, "colors"))
	{
	  color_support();
	}

      //dircheck
      else if(!strcmp(input, "dirchk"))
	{
	  check_directories_and_files();
	}

      //dirpurge
      else if(!strcmp(input, "dirpurge"))
	{
	  purge_directories();
	}
      
      //daemonize
      else if(!strcmp(input, "daemon"))
	{
	  daemonize();
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

  /*
  char *test = prep_output("TEST", "white");
  printf("%s\n", test);

  free(test);
  */
  printf("Deleting previously created directories:\n");
  purge_directories();
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
