#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
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

printf("Checking fork(): ");

if((process_id=fork()) < 0)
  {
check(process_id, "Spawning a child process.");
}else if( process_id == 0)
  {
printf("Child process spawned with its id: %d\n", getpid());
exit(0);
}else if(process_id > 0){

printf("Parent process id: %d\n", getpid());
}

}

#endif /*TEST*/

