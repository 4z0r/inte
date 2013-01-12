#ifndef _functions_h
#define _functions_h

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 256

void check_directories_and_files();
void cut_line(const char);
char* prep_output(const char *, const char*);
void color_support();

#ifndef TEST

#else

int check_fork();

#endif /*TEST*/

#endif /*_functions_h*/
