#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "functions.H"
#include "cfgparse.H"

#ifdef COLORS

#include "colors_debug.H"
#include "colors_table.H"

void prep_output(char **str, char* color)
{
  struct colt *c = (struct colt*) malloc(sizeof(struct colt));

  c->color=NULL;
  c->color_value=NULL;
  c->next_color=NULL;

  load_colors(c);
  print_available_colors(c);
  cleanup_colors_struct(c);
  
  free(c);
}

void color_support()
{
  cut_line('-');
  printf("You terminal supports colors.\n");
  printf("Here's a listing of all the colors I loaded up in a struct for use \n");
  printf("with this programm: \n\n");

  struct colt *c = (struct colt*) malloc(sizeof(struct colt));

  c->color=NULL;
  c->color_value=NULL;
  c->next_color=NULL;


  load_colors(c);
  print_available_colors(c);
  cleanup_colors_struct(c);
  
  cut_line('-');
  printf("\n");
  
  free(c);
}
#else

#include "debug.H"

void prep_output(char **str, char* color)
{
  return;
}

void color_support(){
  log_warn("Sorry mate, you terminal does not seem to support colors.\n");
}
#endif

/*
  check_directories_and_files:

  check for the following directories and files
  and creates / generates them as needed. 

  ~/.inte/scripts/
  ~/.inte/config/config.cfg
  ~/.inte/README

*/

void check_directories_and_files()
{

  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  int status_message_position = w.ws_col;

  char inte_path[MAX_PATH_LENGTH];
  char *home = getenv("HOME");
  char status_message[21];

  printf("\nChecking for needed directories and files:\n");

  sprintf(inte_path, "%s/.inte", home);
  printf(" ->%s ",  inte_path); 

  if(!mkdir(inte_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
    {
      sprintf(status_message, "[ FAILED ]");
      
      /*
	+7:
	
	free spaces 4 
	+ 3 characters from (" ->") when printing the path to be checked
       */
      status_message_position -= strlen(status_message) + 7;

      int i;
      for(i=strlen(inte_path); i<status_message_position; ++i)
	printf("./\b-\b\\\b");

      printf(" %s\n", status_message);

      //create all files and subdirectories

    }else{

    sprintf(status_message, "[ OK ]");
    status_message_position -= strlen(status_message) + 7;
    
    int i;
    for(i=strlen(inte_path); i<status_message_position; ++i)
      printf("./\b-\b\\\b");
    
    printf(" %s\n", status_message);
  }
  
  printf("Done.\n");
}

/*
  cut_line:
  
  gets the winsize and prints the passed in char 
  for every column
*/

void cut_line(char c)
{
  int i;
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  
  for(i=0; i<w.ws_col; ++i)
    printf("%c", c);

  printf("\n");
}

#ifndef TEST

#else

int check_fork()
{
  pid_t process_id;
  
  printf("Checking fork():\n");
  
  /*
    pid = 0 -- child process
    pid > 0 -- parent process
    pid < 0 -- failed to fork
   */
  
  printf(" -> Parent's process id: %d\n", getpid());
  
  if((process_id=fork()) < 0)
    {
      log_err("Could not fork().");
      return 0;
    }else if( process_id == 0)
    {
      printf(" -> Child process spawned with its id: %d\n", getpid());
      exit(0); //kill child process
    }else if(process_id > 0){
    
    /*wait for child to terminate*/
    while((process_id = waitpid(-1, NULL, 0)))
      {
	if(errno == ECHILD)
	  {
	    break;
	  }
      }
  }

  return 1;
}


#endif /*TEST*/

