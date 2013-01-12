#ifndef _colors_debug_h
#define _colors_debug_h

/*
 * Adopted and extended from Zed. A. Shaw's "Learn code the hard way".
 * Ovidiu - Dan Bogat
 * 
 * DATE:    08 January 2013
 * E-MAIL:  a0968382@unet.univie.ac.at
 */

/*
  Colors:

  Black       0;30     Dark Gray     1;30
  Blue        0;34     Light Blue    1;34
  Green       0;32     Light Green   1;32
  Cyan        0;36     Light Cyan    1;36
  Red         0;31     Light Red     1;31
  Purple      0;35     Light Purple  1;35
  Brown       0;33     Yellow        1;33
  Light Gray  0;37     White         1;37
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifndef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "\033[0;37mDEBUG\033[0;0m %s:%d " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno)) 

#define log_err(M, ...) fprintf(stderr, "\033[0;31m[ERROR]\033[0;0m (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "\033[0;33m[WARN]\033[0;0m (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "\033[0;34m[INFO]\033[0;0m (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0;}

#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "\033[0;31mOut of memory.\033[0;0m")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error;}


#endif /*_colors_debug_h*/
