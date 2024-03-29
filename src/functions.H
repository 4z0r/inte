#ifndef _functions_h
#define _functions_h

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 256

void check_directories_and_files();
void purge_directories();
int check_for_directory(const char*);
void handle_directory_creation(const char*);
void handle_directory_deletion(const char*);
void handle_file_creation(const char*);
void handle_file_unlinking(const char*);
void cut_line(const char);
char* prep_output(const char *, const char*);
void color_support();
void daemonize();

#ifdef TEST

int check_fork();

#endif /*TEST*/

#endif /*_functions_h*/
