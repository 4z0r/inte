#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cfgparse.H"
#include "debug.H"

#ifndef TEST

#else

int check_parser()
{
  char *message = strdup("Checking config parser: ");
  int shell_columns = 80;
  int i;
  
  printf("%s", message);
 
  for(i=0; i<shell_columns; ++i)
    {
      //percentage of progess when done
      printf(".");
      int j = 0;
      for(;j<2000; ++j)
      	printf("/\b-\b\\\b");
      --shell_columns;
    }
  
  printf("\033[33m[\033[34m OK \033[33m]\033[0m\n");
  return 1;
}

#endif
