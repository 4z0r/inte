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

char* prep_output(const char *str, const char* color)
{
  struct colt *c = (struct colt*) malloc(sizeof(struct colt));

  c->color=NULL;
  c->color_value=NULL;
  c->next_color=NULL;

  load_colors(c);

  /*
    magic
   */

  char tmp[100] = {};
  char *color_value = return_color_value(c, color);
   
  if(!strcmp(color_value, ""))
    {
  
    }else{
  
    //sprintf(tmp, "%s%s%s%s", "\033[", color_value, str, "\033[0;0m");

    sprintf(tmp, "\033[%s", color_value);
    strcat(tmp, str);
    strcat(tmp, "\033[0;0m");

    cleanup_colors_struct(c);
    free(c);
    return strdup(tmp);
  }
  
  cleanup_colors_struct(c);
  free(c);
  if(color_value) free(color_value);
  return strdup(tmp);
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
  char inte_path[MAX_PATH_LENGTH];
  char *home = getenv("HOME");

  printf("\nChecking for needed directories and files:\n");

  sprintf(inte_path, "%s/.inte", home);
  handle_directory_creation(inte_path);
  sprintf(inte_path, "%s/scripts", inte_path);
  handle_directory_creation(inte_path);
  sprintf(inte_path, "%s/.inte/config", home);
  handle_directory_creation(inte_path);

  printf("Done.\n");
}

/*
  purge_directories():
  
  deletes all directories and files
*/

void purge_directories()
{
  char inte_path[MAX_PATH_LENGTH];
  char *home = getenv("HOME");

  printf("\nDeleting directories and files:\n");

  sprintf(inte_path, "%s/.inte/config", home);
  handle_directory_deletion(inte_path);

  sprintf(inte_path, "%s/.inte/scripts", home);
  handle_directory_deletion(inte_path);

  sprintf(inte_path, "%s/.inte", home);
  handle_directory_deletion(inte_path);

  printf("Done.\n");
}

/*
  handle_directory_creation():
  
 */

void handle_directory_creation(const char *path)
{
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  int status_message_position = w.ws_col;

  char status_message[21];

  printf(" ->%s ",  path); 

  if(!mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
    {
      char *tmp = prep_output("FAIL", "red");
      sprintf(status_message, "[ %s ]", tmp);
      free(tmp);
      
      /*
	+7:
	
	free spaces 4 
	+ 3 characters from (" ->") when printing the path to be checked
      */
      status_message_position -= (strlen(status_message) - 8);
      
      int i;
      for(i=strlen(path); i<status_message_position; ++i)
	printf("./\b-\b\\\b");
      
      printf(" %s\n", status_message);

      char *err_tmp = prep_output("INFO", "lightcyan");
      printf("     [%s] errno: %s\n", err_tmp, clean_errno());
      free(err_tmp);
      
    }else{
    
    char *tmp = prep_output("OK", "blue");
    sprintf(status_message, "[ %s ]", tmp);
    free(tmp);
    
    status_message_position -= (strlen(status_message) - 8);
    
    int i;
    for(i=strlen(path); i<status_message_position; ++i)
      printf("./\b-\b\\\b");
    
    printf(" %s\n", status_message);
  }
  
}

/*
  handle_directory_deletion():
  
 */

void handle_directory_deletion(const char *path)
{
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

  int status_message_position = w.ws_col;

  char status_message[21];

  printf(" ->%s ",  path); 

  if(rmdir(path))
    {
      char *tmp = prep_output("FAIL", "red");
      sprintf(status_message, "[ %s ]", tmp);
      free(tmp);
      
      /*
	+7:
	
	free spaces 4 
	+ 3 characters from (" ->") when printing the path to be checked
      */
      status_message_position -= (strlen(status_message) - 8);
      
      int i;
      for(i=strlen(path); i<status_message_position; ++i)
	printf("./\b-\b\\\b");
      
      printf(" %s\n", status_message);

      char *err_tmp = prep_output("INFO", "lightcyan");
      printf("     [%s] errno: %s\n", err_tmp, clean_errno());
      free(err_tmp);

    }else{
    
    char *tmp = prep_output("OK", "blue");
    sprintf(status_message, "[ %s ]", tmp);
    free(tmp);
    
    status_message_position -= (strlen(status_message) - 8);
    
    int i;
    for(i=strlen(path); i<status_message_position; ++i)
      printf("./\b-\b\\\b");
    
    printf(" %s\n", status_message);
  }
  
}


/*
  cut_line:
  
  gets the winsize and prints the passed in char 
  for every column
*/

void cut_line(const char c)
{
  int i;
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  
  for(i=0; i<w.ws_col; ++i)
    printf("%c", c);

  printf("\n");
}

#ifdef TEST

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

