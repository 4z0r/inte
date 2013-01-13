#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h> //get rows and columns clean instead of getenv
#include "cfgparse.H"

#ifdef COLORS
#include "colors_debug.H"
#include "colors_table.H"
#else
#include "debug.H"
#endif

#ifndef TEST

#else

int check_parser()
{
  struct winsize wsz;
  ioctl(0, TIOCGWINSZ, &wsz);

  char *message = strdup("Checking config parser: ");
  unsigned int i;
  
  printf("%s", message);
  
  for(i=0; i < (wsz.ws_col - strlen(message) - 9); ++i)
    {
      //percentage of progess when done
      printf(".");
      int j = 0;
      for(;j<2000; ++j)
      	printf("/\b-\b\\\b");
    }
  
  printf("   \033[33m[\033[34m OK \033[33m]\033[0m\n");
  return 1;
}

#endif
