#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "functions.H"
#include "debug.H"
#include "cfgparse.H"

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

