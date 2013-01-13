#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([inte], [1.0], [bogat_ovidiu@hotmail.com])
AC_CONFIG_SRCDIR([src/main.C])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lcolt':
AC_CHECK_LIB([colt], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h sys/ioctl.h sys/socket.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_PID_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([mkdir rmdir strdup])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
